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

char *mx_file_input_cat(t_st *st) {
    char *tmp = NULL;
    char *res = NULL;

    if (st->cin > 0) {
        for (int i = 0; i < st->cin; i++)
            tmp = multinput(st->cinput[i], tmp, NULL);
        res = tmp;
    }
    return res;
}
