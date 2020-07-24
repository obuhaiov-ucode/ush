#include "ush.h"

static char *multinput(char *file, char *tmp, char *res) {
    FILE *mf;
    char line[8192];
    int n = 0;

    memset(line, 0, 8192);
    if ((mf = fopen(file, "r")) == NULL)
        perror("ush: ");
    if ((n = fread(line, sizeof(char), 8192, mf)) < 0)
        perror("ush: ");
    fclose(mf);
    n = mx_strlen(line);
    for (; line[n] != '\n'; n--);
    line[n] = '\0';
    if (tmp != NULL) {
        res = mx_strjoin(tmp, line);
        mx_del_chararr(tmp);
    }
    else
        res = strdup(line);
    return res;
}

char *mx_file_input(t_st *st, int pipe) {
    char *tmp = NULL;
    char *res = NULL;

    if (st->in[pipe] > 0) {
        for (int i = 0; i < st->in[pipe]; i++)
            tmp = multinput(st->input[pipe][i], tmp, NULL);
        if (st->fbuf[pipe - 1] != NULL && pipe > 0) {
            res = mx_strjoin(st->fbuf[pipe - 1], tmp);
            mx_del_chararr(tmp);
        }
        else
            res = tmp;
    }
    else if (st->fbuf[pipe - 1] != NULL && pipe > 0)
        res = mx_strdup(st->fbuf[pipe - 1]);
    return res;
}
