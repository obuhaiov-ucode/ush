#include "ush.h"

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
