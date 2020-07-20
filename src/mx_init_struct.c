#include "ush.h"

char **mx_alias_arr() {
    char **arr = (char**)malloc(sizeof(char*) * 1);

    arr[0] = NULL;
    return arr;
}

void mx_init_struct(t_st *st, char **env) {

    st->env = env;
    st->alias = mx_alias_arr();
    st->status = 0;
}
