#include "ush.h"

static int count_noslash(char *c, int i) {
    for (; c[i] != '\0'; i++) {
        if (c[i] == ' ' && c[i - 1] != '\\') {
            return i;
        }
    }
    return i;
}

static char *get_tok(char *c, int i, int n, int num) {
    char *res = NULL;

    for (int j = i; c[j] != '\0' && j < i + n; j++) {
        if (c[j] == ' ' && c[j - 1] == '\\')
            num++;
    }
    num = n - num;
    res = malloc(sizeof(char) * (num + 1));
    res[num] = '\0';
    num = 0;
    for (int j = i; c[j] != '\0' && j < i + n;) {
        if (c[j + 1] == ' ' && c[j] == '\\') {
            res[num++] = c[j + 1];
            if (c[j + 2] != '\0')
                j += 2;
        }
        else
            res[num++] = c[j++];
    }
    return res;
}

static int midl_pars_cd(char *c, t_st *st, char **tokens) {
    if (c[st->i] == '-' && c[st->i - 1] == ' ') {
        tokens[st->k++] = strndup(&c[st->i], strcspn(&c[st->i], " \0"));
        st->i += strcspn(&c[st->i], " \0") - 1;
    }
    else {
        st->n = strcspn(&c[st->i], " \0");
        if (c[st->i + st->n - 1] != '\\') {
            tokens[st->k++] = strndup(&c[st->i], st->n);
            st->i += strcspn(&c[st->i], " \0") - 1;
        }
        else {
            st->n = count_noslash(c, st->i);
            tokens[st->k++] = get_tok(c, st->i, st->n - st->i, 0);
            st->i = st->n - 1;
        }
    }
    return st->i;
}


char **mx_streams_cd(char *c, t_st *st, int bufsize, char *main_c) {
    char **tokens = malloc(bufsize * sizeof(char*));
    st->i = strcspn(c, " \0");
    st->k = 1;
    st->n = 0;

    tokens[0] = main_c;
    for (; c[st->i] != '\0'; st->i++) {
        if (c[st->i] != ' ')
            st->i = midl_pars_cd(c, st, tokens);
        tokens = mx_split_backup(tokens, bufsize, st->k);
        if (st->k >= bufsize)
            bufsize += 64;
    }
    tokens[st->k] = NULL;
    return tokens;
}
