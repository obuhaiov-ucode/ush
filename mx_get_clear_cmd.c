#include "ush.h"

char *mx_get_clear_cmd(char *cmd, int k) {
    int n = mx_strlen(cmd) - 1;
    char line[1024];
    char *res = NULL;

    for (int i = 0; cmd[i] != '\0'; i++) {
        if ((cmd[i] == 39 || cmd[i] == '"') && (i != 0 && i != n))
            line[k++] = cmd[i];
        else if (cmd[i] != 39 && cmd[i] != '"')
            line[k++] = cmd[i];
    }
    line[k] = '\0';
    n = mx_strlen(line);
    res = mx_strdup(line);
    mx_del_chararr(cmd);
    return res;
}
