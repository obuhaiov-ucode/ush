#include "ush.h"

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
    switch (cmd->builtin) {
        case b_cd:
            mx_cd_builtin(cmd->argv, app);
            break;
        case b_which:
            mx_which(cmd->argv, app);
            break;
        case b_echo:
            mx_echo_builtin(cmd->argv);
            break;
        case b_pwd:
            mx_pwd_builtin(cmd->argv, app);
            break;
        case b_env:
            mx_env_builtin(cmd->argv) ;
            break;
        case b_export:
            mx_builtin_export(app, cmd);
            break;
        case b_unset:
            mx_builtin_unset(cmd, app);
            break;
        case b_exit:
            exit(0);
            break;
        default:
            break;
    }
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
        fprintf(stderr, "%s not found\n", cmd->argv[1]);
    else
        fprintf(stderr, "ush: command not found: %s\n", cmd->argv[0]);
}

int mx_streams(t_st *st, char **tokens, t_app *app) {
    t_cmd *cmd = malloc(sizeof(t_cmd));
    
    cmd->argc = 0;
    cmd->argv = tokens;
    for (int i = 0; tokens[i] != NULL; i++)
        cmd->argc++;
    eval(app, cmd);
    return st->status;
}
