#include "ush.h"

char *mx_file_input_cat(t_st *st) {
    char *tmp = NULL;
    char *res = NULL;
    int n = 0;

    if (st->cin > 0) {
        for (int i = 0; i < st->cin; i++)
            tmp = mx_multinput(st->cinput[i], tmp, NULL);
        n = mx_strlen(tmp);
        // if (tmp[n - 1] == '\n')
        //     res = mx_strndup(tmp, n);
        // else 
            res = mx_strdup(tmp);
        mx_del_chararr(tmp);
    }
    return res;
}
