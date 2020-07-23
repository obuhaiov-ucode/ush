#include "ush.h"

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
