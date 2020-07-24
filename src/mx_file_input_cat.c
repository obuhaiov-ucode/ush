#include "ush.h"

static char *multinput(char *file, char *tmp, char *res) {
    FILE *mf;
    char line[8192];

    if ((mf = fopen(file, "r")) == NULL)
        perror("ush: ");
    while(!feof(mf))
        fgets(line, 8191, mf);
    fclose(mf);
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
        for (int i = 0; i < st->cin; i++) {
            printf("in = %d = %s\n", i, st->cinput[i]);
            tmp = multinput(st->cinput[i], tmp, NULL);
            printf("tmp = %d = %s\n", i, tmp);
        }
            
        res = tmp;
        //printf("All input = %s\n", res);
    }
    return res;
}
