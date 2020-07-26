#include "ush.h"

char *mx_free_str(char *str, char *buf) {
    char *tmp = NULL;

    mx_strdel(&str);
    tmp = mx_strdup(buf);
    mx_strdel(&buf);
    return tmp;
}
