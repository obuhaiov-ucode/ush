#include "ush.h"

char *mx_shlvl_check(char *tok, int n, char *tmp) {
    tmp = getenv("SHLVL");
    if (mx_strcmp(tmp, "1") == 0)
        setenv("SHLVL", "2", 1);
    if (mx_strcmp(tok, "./ush") == 0 && tmp != NULL) {
        n = atoi(tmp) + 1;
        tmp = mx_itoa(n);
        tmp = mx_strjoin("unset SHLVL ; export SHLVL=", tmp);
        return tmp;
    }
    else if (tmp == NULL)
        setenv("SHLVL", "1", 1);
    return tok;
}
