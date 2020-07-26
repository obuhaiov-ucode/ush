#include "ush.h"

int mx_not_need(char b, char c, char d) {
    if ((c == 39 || c == '"') && b == '\\')
        return 1;
    if ((c == 39 || c == '"') && b != '\\')
        return 0;
    return 1;
}
