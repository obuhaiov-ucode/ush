#include "ush.h"

char *mx_multinput(char *file, char *tmp, char *res) {
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
    // for (; line[n] != '\n'; n--);
    // line[n + 1] = '\0';
    if (tmp != NULL) {
        res = mx_strjoin(tmp, line);
        mx_del_chararr(tmp);
    }
    else
        res = strdup(line);
    return res;
}
