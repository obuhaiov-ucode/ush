#include "ush.h"

static int check_any_cmd(char *c, int n) {
    for (; c[n] == ' ' && c[n] != '\0'; n++);
    if (c[n] == '\\' && c[n + 1] == '\0')
        return 0;
    n = 0;
    for (int i = 0; c[i] != '\0';) {
        for (; c[i] == ' ' && c[i] != '\0'; i++);
        if (!(c[i] == '|' || c[i] == '&' || c[i] == ';' || c[i] == '\0')) {
            for (; c[i] != '|' && c[i] != '&' && c[i] != ';'
                && c[i] != '\0' && c[i] != ' '; i++)
                n++;
        }
        if (n == 0)
            return 0;
        break;
    }
    return 1;
}

int mx_check_cmd(char *c) {
    if (check_any_cmd(c, 0)) {
        for (int i = 0; c[i] != '\0';) {
            for (; c[i] == ' ' && c[i] != '\0'; i++);
            if (c[i] == '|' || c[i] == '&' || c[i] == ';' || c[i] == '\0')
                return 0;
            else
                for (; c[i] != '|' && c[i] != '&' && c[i] != ';' 
                    && c[i] != '\0'; i++); 
            if (c[i] == '|' || c[i] == '&' || c[i] == ';') {
                if (c[i] == '|' || c[i] == '&')
                    i += 2;
                else
                    i++;
            }
        }
    }
    else
        return 0;
    return 1;
}
