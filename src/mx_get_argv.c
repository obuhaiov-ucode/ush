#include "ush.h"

char *mx_get_argv(char *file, char *res) {
    FILE *mf;
    char line[8192];

    if ((mf = fopen(file, "r")) == NULL)
        return NULL;
    while(!feof(mf))
        fgets(line, 8191, mf);
    fclose(mf);
    res = mx_strdup(line);
    return res;
}
