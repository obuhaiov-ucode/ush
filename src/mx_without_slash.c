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

int mx_get_start_pos(char *del, int n) {
    for (int i = 0; del[i] != '\0'; i++) {
        if (del[i + 1] == del[n] && del[i] != '\\')
            return i + 1;
    }
    return -1;
}

static char *cycle_handler(char *del, int n, char tmp[1024], int k) {
    char *res = NULL;
    int start = mx_get_start_pos(del, n);

    if (start > -1 && start != n) {
        for (int i = 0; del[i] != '\0'; i++) {
            if (start != i && n != i)
                tmp[k++] = del[i];
        }
        res = mx_strndup(tmp, k);
        mx_del_chararr(del);
    }
    else
        return del;
    return res;
}


int mx_get_end_pos(char *del) {
    int n = mx_strlen(del) - 1;

    for (; n > 0 ; n--) {
        if ((del[n] == 39 || del[n] == '"')
            && n > 0 && del[n - 1] != '\\')
            return n;  
    }
    return -1;
}

static char *without_qoutes(char *del, char *c, char *res, int n) {
    char tmp[1024];

    if (del != NULL) {
        if ((n = mx_get_end_pos(del)) != -1) {
            memset(tmp, 0, 1024);
            res = cycle_handler(del, n, tmp, 0);
        }
    }
    else if ((n = mx_get_end_pos(c)) != -1) {
        memset(tmp, 0, 1024);
        res = cycle_handler(c, n, tmp, 0);
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
