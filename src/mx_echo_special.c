#include "ush.h"

int mx_echo_special(char c) {
    if (c == 't' || c == 'v' || c == 'r' || c == 'n' || c == ' '
        || c == 'a' || c == 'b' || c == 'c' || c == 'f')
        return 1;
    return 0;
}
