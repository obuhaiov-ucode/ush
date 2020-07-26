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
