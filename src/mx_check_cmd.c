#include "ush.h"

static int check_any_cmd(char *c, int n, int i, int k) {
    for (; c[n] != '\0'; n++) {
        for (; c[n] != '\0' && c[i] != '\\'; n++);
        if ()
        for (i = n; c[i] == '\\' && c[i] != '\0'; i++);
        printf("n = %d  i = %d\n", n, i);
        if (i - n > 0 && (i - n) % 2 == 1 && mx_any_count(c[i]) != 1) {
            write (2, "Odd number of backslashes.\n", 27);
            exit(1);
        }
    }
    for (int i = 0; c[i] != '\0';) {
        for (; c[i] == ' ' && c[i] != '\0'; i++);
        if (!(c[i] == '|' || c[i] == '&' || c[i] == ';' || c[i] == '\0')) {
            for (; (c[i] != '|' && c[i] != '&' && c[i] != ';' && c[i] != '\0'
                && c[i] != ' ') || (c[i] == '\\' && c[i + 1] == '\\'); i++)
                k++;
        }
        if (k == 0)
            return 0;
        break;
    }
    return 1;
}

int mx_check_cmd(char *c) {
    if (check_any_cmd(c, 0, 0, 0)) {
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
