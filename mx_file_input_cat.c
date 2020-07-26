#include "ush.h"

char *mx_file_input_cat(t_st *st) {
    char *tmp = NULL;
    char *res = NULL;

    if (st->cin > 0) {
        for (int i = 0; i < st->cin; i++)
            tmp = mx_multinput(st->cinput[i], tmp, NULL);
        res = mx_strdup(tmp);
        mx_del_chararr(tmp);
    }
    return res;
}
