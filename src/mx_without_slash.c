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

static char *midl_without(char *c, char *res) {
    char tmp[1024];
    int n = 0;

    for (int i = 0; c[i] != '\0'; i++) {
        if ((c[i + 1] == '"' || c[i + 1] == 39)
            && (c[i] == ' ' || c[i + 2] == '\0'))
            tmp[n++] = c[i++];
        else
            tmp[n++] = c[i];
    }
    res = mx_strdup(tmp);
    return res;
}

static char *without_qoutes(char *del, char *c, char *res) {
    char tmp[1024];
    int n = 0;

    if (del != NULL) {
        memset(tmp, 0, 1024);
        for (int i = 0; del[i] != '\0'; i++) {
            if ((del[i + 1] == '"' || del[i + 1] == 39)
                && (del[i] == ' ' || del[i + 2] == '\0'))
                tmp[n++] = del[i++];
            else
                tmp[n++] = del[i];
        }
        res = mx_strdup(tmp);
    }
    else
        res = midl_without(c, NULL);
    mx_del_chararr(del);
    mx_del_chararr(c);
    return res;
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
        res = mx_strdup(line);
    }
    res = without_qoutes(res, c, NULL);
    return res;
}
