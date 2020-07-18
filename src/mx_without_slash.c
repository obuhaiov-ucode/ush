#include "ush.h"

char *mx_without_slash(char *c, char *res, int k, int n) {
    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] == '\\' && c[i + 1] == '\\') {
            for (k = i; c[k] == '\\'; k++);
            if ((k - i) % 2 == 0)
                n += (k - i) / 2;
            else if (mx_any_count(c[k]))
                n += (k - i - 1) / 2;
            else {
                write(2, "Odd number of back slashes.\n", 28);
                exit(1);
            }
            i = k - 1;
        }
        else if (c[i] != '\\')
            n++;
    }
    //make
    // printf("%d  %d\n", n, mx_strlen(c));
    if (n != mx_strlen(c)) {
        res = malloc(sizeof(char) * (n + 1));
        res[n] = '\0';
        n = 0;
        for (int i = 0; c[i] != '\0'; i++) {
            if (c[i] == '\\' && c[i + 1] == '\\') {
                for (k = i; c[k] == '\\'; k++);
                if ((k - i) % 2 == 0) {
                    for (int j = 0; j < (k - i) / 2; j++)
                        res[n++] = c[i];
                }
                else if (mx_any_count(c[k])) {
                    for (int j = 0; j < (k - i - 1) / 2; j++)
                        res[n++] = c[i];
                }
                i = k - 1;
            }
            else if (c[i] != '\\')
                res[n++] = c[i];
        }
        mx_del_chararr(c);
        return res;
    }
    return c;
}
