#include "ush.h"

void mx_builtin_exit(t_cmd *cmd, t_app *app) {
    int stat = 0;

    if (cmd->argv[1] != NULL) {
        stat = atoi(cmd->argv[1]);
        exit(stat);
    }
    else
        exit(app->status);
}

enum builtin_t parse_builtin(t_cmd *cmd) {
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

void run_system_command(t_cmd *cmd) {
    pid_t childPid;

    if ((childPid = fork()) < 0)
        fprintf(stderr, "fork() error\n");
    else if (childPid == 0) {
        if (execvp(cmd->argv[0], cmd->argv) < 0) {
            printf("ush: %s: command not found:\n", cmd->argv[0]);
            exit(1);
        }
    }
    else 
        wait(&childPid);
}

void run_builtin_command(t_cmd *cmd, t_app *app) {
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

int mx_without_path(t_app *app, t_cmd *cmd) {
    if ((app->env_path_deleted == true && (cmd->builtin == b_cd
          || cmd->builtin == b_pwd || cmd->builtin == b_echo
          || cmd->builtin == b_exit || cmd->builtin == b_unset
          || cmd->builtin == b_export)) || app->env_path_deleted == false) {
        return 1;
    }
    return 0;
}

int mx_all_builtin(t_cmd *cmd, int k) {
    if (cmd->argv[k] != NULL && cmd->argv[k][0] != '-') {
        if (mx_strcmp(cmd->argv[k], "cd") == 0
            || mx_strcmp(cmd->argv[k], "pwd") == 0
            || mx_strcmp(cmd->argv[k], "echo") == 0
            || mx_strcmp(cmd->argv[k], "exit") == 0
            || mx_strcmp(cmd->argv[k], "unset") == 0
            || mx_strcmp(cmd->argv[k], "export") == 0
            || mx_strcmp(cmd->argv[k], "which") == 0)
        return k;
    }
    return 0;
}

void mx_which_unset(t_cmd *cmd, int cur) {
    for (int i = cur; cmd->argv[i] != NULL; i++) {
        if ((cur = mx_all_builtin(cmd, i)) > 0)
            fprintf(stderr, "%s: ush built-in command\n\r", cmd->argv[cur]);
        else if (cmd->argv[i] != NULL && cmd->argv[i][0] != '-')
            fprintf(stderr, "%s not found\n\r", cmd->argv[i]);
        else if (cmd->argv[i] != NULL && cmd->argv[i][0] != '-')
            fprintf(stderr, "%s not found\n\r", cmd->argv[i]);
    }
}

void eval(t_app *app, t_cmd *cmd) {
    cmd->builtin = parse_builtin(cmd);
    if (cmd->argv[0] == NULL) return;
    if (mx_without_path(app, cmd)) {
        if (cmd->builtin == b_none)
            run_system_command(cmd);
        else 
            run_builtin_command(cmd, app);
    }
    else if (cmd->builtin == b_which)
        mx_which_unset(cmd, 1);
    else
        fprintf(stderr, "ush: command not found: %s\n", cmd->argv[0]);
}

int mx_shlvl_check(char *cmd, int n, char *tmp) {
    tmp = getenv("SHLVL");
    if (mx_strcmp(cmd, "./ush") == 0) {
        n = atoi(tmp) + 1;
        sprintf(tmp, "%d", n);
        //printf("%s\n", tmp);
        unsetenv("SHLVL");
        setenv("SHLVL", tmp, 1);
        return 0;
    }
    return 1;
}

int mx_status_check(char **tokens, t_app *app, char *tmp) {
    if (mx_strcmp(tokens[0], "echo") && tokens[1][0] == '$' && tokens[1][1] == '?') {
        printf("HERE\n");
        sprintf(tmp, "%d\n", app->status);
        write(1, tmp, mx_strlen(tmp));
        return 0;
    }
    return 1;
}

int mx_streams(t_st *st, char **tokens, t_app *app) {
    t_cmd *cmd = malloc(sizeof(t_cmd));
    
    app->status = st->status;
    if (mx_shlvl_check(tokens[0], 0, NULL) || mx_status_check(tokens, app, NULL)) {
        for (int i = 0; tokens[i] != NULL; i++)
            printf("%s\n", tokens[i]);
        cmd->argc = 0;
        cmd->argv = tokens;
        for (int i = 0; tokens[i] != NULL; i++)
            cmd->argc++;
        eval(app, cmd);
    }
    else
        st->status = 0;

    return st->status;
}
