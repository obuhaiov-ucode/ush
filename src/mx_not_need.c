#include "ush.h"

int mx_not_need(char b, char c) {
    if ((c == 39 || c == '"') && b != '\\')
        return 0;
    return 1;
}
