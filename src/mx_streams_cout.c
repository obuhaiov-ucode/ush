#include "ush.h"

static int count_out(char **tokens) {
    int i = 0;

    for (; tokens[i] != NULL; i++);
    return i;
}

char **mx_streams_cout(t_st *st, char **tokens, int j) {
    int n = st->cout;
    char **tok = NULL;
    int i = count_out(tokens);

    tok = (char **)malloc(sizeof(char *) * ((i - (n * 2)) + 1));
    tok[i - (n * 2)] = NULL;
    st->coutput = (char **)malloc(sizeof(char *) * (n + 1));
    st->coutput[n] = NULL;
    n = 0;
    for (i = 0; tokens[i] != NULL; i++) {
        if (!(((tokens[i][0] == '>' && i == 0)
            || (tokens[i][0] == '>' && tokens[i - 1][0] != '>'))
            && tokens[i + 1] != NULL && tokens[i + 1][0] != '>'))
            tok[n++] = mx_strdup(tokens[i]);
        else {
            st->coutput[j++] = mx_strdup(tokens[i + 1]);
            i++;
        }
    }
    return tok;
}
