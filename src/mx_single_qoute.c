#include "ush.h"

int mx_single_qoute(char *c) {
    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] == ' ' && c[i + 1] == 39)
            return 0;
    }
    return 1;
}
