#include "ush.h"

char **mx_weird_slash(char **tok, char **res, t_st *st, char *c) {
    char *main_c = NULL;
    char tmp[8192];
    int n = 0;

    for (int i = 0; tok[i] != NULL; i++) {
        for (int j = 0; tok[i][j] != '\0'; j++) 
            tmp[n++] = tok[i][j];
        if (tok[i + 1] != NULL)
            tmp[n++] = ' ';
    }
    tmp[n] = '\0';
    c = mx_strdup(tmp);
    main_c = strndup(c, strcspn(c, " \0"));
    res = mx_streams_cd(c, st, 64, main_c);
    mx_del_strarr(&tok);
    return res;
}
