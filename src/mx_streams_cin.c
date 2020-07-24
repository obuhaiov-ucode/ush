#include "ush.h"

static int count_in(char **tokens) {
    int i = 0;

    for (; tokens[i] != NULL; i++);
    return i;
}

char **mx_streams_cin(t_st *st, char **tokens, int j) {
    int n = st->cin;
    char **tok = NULL;
    int i = count_in(tokens);
    int k = 0;

    tok = (char **)malloc(sizeof(char *) * ((i - (n * 2)) + 1));
    tok[i - (n * 2)] = NULL;
    st->cinput = (char **)malloc(sizeof(char *) * (n + 1));
    st->cinput[n] = NULL;
    for (i = 0; tokens[i] != NULL; i++) {
        if (!(((tokens[i][0] == '<' && i == 0)
            || (tokens[i][0] == '<' && tokens[i - 1][0] != '<'))
            && tokens[i + 1] != NULL && tokens[i + 1][0] != '<'))
            tok[k++] = mx_strdup(tokens[i]);
        else if (j < n) {
            st->cinput[j++] = mx_strdup(tokens[i + 1]);
            i++;
        }
    }
    return tok;
}
