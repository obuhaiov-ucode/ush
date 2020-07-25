#include "ush.h"

static int midl_check(char *c, int i, int k) {
    for (; c[i] != '\0';) {
        for (; c[i] == ' ' && c[i] != '\0'; i++);
        if (!(c[i] == '|' || c[i] == '&' || c[i] == ';' || c[i] == '\0')) {
            for (; (c[i] != '|' && c[i] != '&' && c[i] != ';' && c[i] != '\0'
                && c[i] != ' ') || (c[i] == '\\' && c[i + 1] == '\\'
                && c[i + 1] != '\0'); i++)
                k++;
        }
        if (k == 0)
            return 0;
        break;
    }
    return 1;
}

static int check_any_cmd(char *c, int n, int i) {
    for (; c[n] != '\0'; n++) {
        for (; c[n] != '\0' && c[n] != '\\'; n++);
        for (i = n; c[i] == '\\' && c[i] != '\0'; i++);
        if ((i - n) % 2 == 1 && c[i] == '\0') {
            write (2, "Odd number of backslashes.\n", 27);
            exit(1);
        }
        n = i;
    }
    if (n > 1 && c[n - 1] == '\\' && c[n - 2] == ' ') {
        write (2, "Odd number of backslashes.\n", 27);
        exit(1);
    }
    if (midl_check(c, 0, 0))
        return 1;
    return 0;
}

int mx_check_cmd(char *c, int i) {
    if (check_any_cmd(c, 0, 0)) {
        for (i = 0; c[i] != '\0';) {
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
