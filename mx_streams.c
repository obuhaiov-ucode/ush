#include "ush.h"

static enum builtin_t parse_builtin(t_cmd *cmd) {
    if (!strcmp(cmd->argv[0], "cd")) 
        return b_cd;
    else if (!strcmp(cmd->argv[0], "which"))
        return b_which;
    else if (!strcmp(cmd->argv[0], "echo"))
        return b_echo;
    else if (!strcmp(cmd->argv[0], "pwd"))
        return b_pwd;
    else if (!strcmp(cmd->argv[0], "env"))
        return b_env;
    else if (!strcmp(cmd->argv[0], "export"))
        return b_export;
    else if (!strcmp(cmd->argv[0], "unset"))
        return b_unset;
    else if (!strcmp(cmd->argv[0], "exit"))
        return b_exit;
    else 
        return b_none;
}

static void run_system_command(t_cmd *cmd, t_app *app) {
    pid_t childPid;
    int n = mx_strlen(cmd->argv[0]) - 1;

    if ((childPid = fork()) < 0)
        perror("ush: ");
    else if (childPid == 0) {
        if ((cmd->argv[0][0] == 39 && cmd->argv[0][n] == 39)
            || (cmd->argv[0][0] == '"' && cmd->argv[0][n] == '"'))
            cmd->argv[0] = mx_get_clear_cmd(cmd->argv[0], 0);
        if (execvp(cmd->argv[0], cmd->argv) < 0) {
            fprintf(stderr, "ush: command not found: %s\n", cmd->argv[0]);
            app->status = 127;
            exit(127);
        }
    }
    if (!WIFEXITED(app->status) && !WIFSIGNALED(app->status))
        waitpid(childPid, &app->status, WUNTRACED);
    app->status = WEXITSTATUS(app->status);
    wait(&childPid);
}

static void run_builtin_command(t_cmd *cmd, t_app *app) {
    if (cmd->builtin == b_cd)
        app->status = mx_cd_builtin(cmd->argv, app);
    else if (cmd->builtin == b_which)
        app->status = mx_which(cmd->argv, app);
    else if (cmd->builtin == b_echo)
        app->status = mx_echo_builtin(cmd->argv, app);
    else if (cmd->builtin == b_pwd)
        app->status = mx_pwd_builtin(cmd->argv, app);
    else if (cmd->builtin == b_env)
        app->status = mx_env_builtin(cmd->argv);
    else if (cmd->builtin == b_export)
        app->status = mx_builtin_export(app, cmd);
    else if (cmd->builtin == b_unset)
        app->status = mx_builtin_unset(cmd, app);
    else if (cmd->builtin == b_exit)
        mx_builtin_exit(cmd, app);
    else
        return;
}

static void eval(t_app *app, t_cmd *cmd) {
    cmd->builtin = parse_builtin(cmd);
    if (cmd->argv[0] == NULL) 
        return;
    if (mx_without_path(app, cmd)) {
        if (cmd->builtin == b_none)
            run_system_command(cmd, app);
        else 
            run_builtin_command(cmd, app);
    }
    else if (cmd->builtin == b_which)
        mx_which_unset(cmd, 1);
    else
        fprintf(stderr, "ush: command not found: %s\n", cmd->argv[0]);
}

int mx_streams(t_st *st, char **tokens, t_app *app) {
    t_cmd *cmd = malloc(sizeof(t_cmd));
    
    app->have_sub = st->have_sub;
    if (mx_status_check(tokens, app)) {
        cmd->argc = 0;
        cmd->argv = tokens;
        for (int i = 0; tokens[i] != NULL; i++)
            cmd->argc++;
        eval(app, cmd);
    }
    else
        st->status = 0;
    st->have_sub = app->have_sub;
    return st->status;
}
