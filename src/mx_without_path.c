#include "ush.h"

int mx_without_path(t_app *app, t_cmd *cmd) {
    if ((app->env_path_deleted == true && (cmd->builtin == b_cd
        || cmd->builtin == b_pwd || cmd->builtin == b_echo
        || cmd->builtin == b_exit || cmd->builtin == b_unset
        || cmd->builtin == b_export)) || app->env_path_deleted == false)
        return 1;
    return 0;
}
