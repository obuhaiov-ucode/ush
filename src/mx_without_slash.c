#include "ush.h"

static int count_new(char *c, int n, int k, int i) {
    for (i = 0; c[i] != '\0'; i++) {
        if (c[i] == '\\' && c[i + 1] == '\\') {
            for (k = i; c[k] == '\\'; k++);
            if ((k - i) % 2 == 0) {
                n += (k - i) / 4;
                if ((k - i) % 4 > 0)
                    n++;
            }
            else if (mx_any_count(c[k]) && (k - i) > 2) {
                n += (k - i - 1) / 4;
                if ((k - i - 1) % 4 > 0)
                    n++;
            }
            i = k - 1;
        }
        else if (c[i] != '\\')
            n++;
    }
    return n;
}

static int count_slash(char *c, int i, int n, int k) {
    if (c[i] == '\\' && c[i + 1] == '\\') {
        for (k = i; c[k] == '\\'; k++);
        if ((k - i) % 2 == 0) {
            if (c[i + 2] == '\\') {
                for (int j = 0; j < (k - i) / 4; j++)
                    n++;
                if ((k - i) % 4 > 0)
                    n++;
            }
            else
                n++;
        }
        else if (mx_any_count(c[k]) && (k - i) > 2) {
            for (int j = 0; j < (k - i - 1) / 4; j++)
                n++;
            if ((k - i - 1) % 4 > 0)
                n++;
        }
    }
    return n;
}

char *mx_without_slash(char *c, char *res, int k, int n) {
    if ((n = count_new(c, 0, 0, 0)) != mx_strlen(c)) {
        res = malloc(sizeof(char) * (n + 1));
        res[n] = '\0';
        n = 0;
        for (int i = 0; c[i] != '\0'; i++) {
            k = count_slash(c, i, 0, 0);
            for (int j = 0; j < k; j++)
                res[n++] = c[i];
            for (; c[i] == '\\' && c[i] != '\0'; i++);
            if (c[i] != '\\')
                res[n++] = c[i];
        }
        mx_del_chararr(c);
        return res;
    }
    return c;
}
