#include "ush.h"

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
        else if (mx_any_count(c[k]) && k - i > 2) {
            for (int j = 0; j < (k - i - 1) / 4; j++)
                n++;
            if ((k - i - 1) % 4 > 0)
                n++;
        }
    }
    return n;
}

static char *cycle_handler(char *del, int n, char tmp[1024]) {
    char *res = NULL;

    for (int i = 0; del[i] != '\0'; i++) {
        if ((del[i + 1] == '"' || del[i + 1] == 39)
            && (del[i] == ' ' || del[i + 2] == '\0'))
            tmp[n++] = del[i++];
        else
            tmp[n++] = del[i];
        }
    res = mx_strndup(tmp, n);
    mx_del_chararr(del);
    return res;
}

static char *midl_without(char *c, char *res, int n) {
    char tmp[1024];
    int k = mx_strlen(c) - 1;

    if (c[k] == 39 || c[k] == '"') {
        res = cycle_handler(c, n, tmp);
    }
    else
        return c;
    return res;
}

static char *without_qoutes(char *del, char *c, char *res, int n) {
    char tmp[1024];

    if (del != NULL) {
        n = mx_strlen(del) - 1;
        if (del[n] == 39 || del[n] == '"') {
            n = 0;
            memset(tmp, 0, 1024);
            res = cycle_handler(del, n, tmp);
        }
    }
    else {
        if (del != NULL)
            res = midl_without(del, NULL, 0);
        else if (c != NULL)
            res = midl_without(c, NULL, 0);
    }
    if (res != NULL)
        return res;
    return del;
}

char *mx_without_slash(char *c, char *res, int k, int n) {
    char line[1024];

    if (!(mx_strlen(c) > 6 && c[5] == '-' && c[6] == 'E')) {
        memset(line, 0, 1024);
        for (int i = 0; c[i] != '\0'; i++) {
            k = count_slash(c, i, 0, 0);
            if (c[i] == '\\' && mx_echo_special(c[i + 1]))
                k = 1;
            for (int j = 0; j < k; j++)
                line[n++] = c[i];
            for (; c[i] == '\\' && c[i] != '\0'; i++);
            if (c[i] != '\\' || mx_not_need(c[i], c[i + 1]))
                line[n++] = c[i];
            if (c[i] == '\\' && mx_echo_special(c[i + 1]))
                line[n++] = c[i];
        }
        res = mx_strndup(line, n);
    }
    res = without_qoutes(res, c, NULL, 0);
    return res;
}
