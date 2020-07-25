#include "ush.h"

char *mx_free_str(char *str, char *buf) {
    //char *tmp = mx_strdup(str);
    mx_strdel(&str);
    str = mx_strdup(buf);
    mx_strdel(&buf);
    return str;
}

