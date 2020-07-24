#include "ush.h"

static char *cmd_del_spaces(char *cmd) {
    char *tmp = NULL;
    int n = mx_strlen(cmd) - 1;
    int start = 0;
    int end = 0;

    if (cmd[start] == '{') {
        for (;(cmd[start] == '{' || cmd[start] == ' ')
        && cmd[start] != '\0'; start++);
    }
    if (cmd[n] == '}') {
        for (;(cmd[n] == '}' || cmd[n] == ' ') && n != 0; n--)
            end++;
    }
    if (start || end) {
        tmp = mx_strndup(&cmd[start], mx_strlen(&cmd[start]) - end);
        mx_del_chararr(cmd);
        return tmp;
    }
    return cmd;
}

static char **midl_pars(t_st *st, char *c, int k, int bufsize) {
    char **tokens = malloc(bufsize * sizeof(char*));

    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] == '|' || c[i] == '<' || c[i] == '>') {
            tokens[k++] = strndup(&c[i], 1);
            mx_counter(c[i], '|', st->pipe);
        }
        else if (c[i] != ' ') {
            tokens[k++] = strndup(&c[i], strcspn(&c[i], " <>|"));
            i += strcspn(&c[i], " <>|") - 1;
        }
        tokens = mx_split_backup(tokens, bufsize, k);
        if (k >= bufsize)
            bufsize += 64;
    }
    tokens[k] = NULL;
    return tokens;
}

static int no_buf(char *c, int i, int n) {
    for (; c[n] != '\0'; n++) {
        for (; c[n] != '\0' && c[n] != '|' && c[n] != '<' 
            && c[n] != '>'; n++);
        for (; c[n] != '\0' && c[n] != '\\' && c[n] != '|' && c[n] != '<'
            && c[n] != '>'; n++);
        for (i = n; c[i] == '\\' && c[i] != '\0' && c[i] != '|'
            && c[i] != '<' && c[i] != '>'; i++);
        if ((i - n) % 2 == 0 && (c[i] == '|' || c[i] == '<' || c[i] == '>'))
            return 0;
        n = i;
    }
    return 1;
}

// static int streams_echo(char *main_c, t_st *st, t_config* term, char *c) {
//     char **tokens = malloc(sizeof(char *) * 3);
//     char **res = NULL;

//     res = mx_streams_cd(c, st, 64, main_c);
//     tokens[0] = mx_strdup(main_c);
//     tokens[1] = mx_echo_builtin(res, (t_app *)term->app);
//     tokens[2] = NULL;
//     mx_del_strarr(&res);
//     st->status = mx_streams(st, tokens, (t_app *)term->app);
//     return st->status;
// }

int mx_command_pars(t_st *st, char *c, char *main_c, t_config* term) {
    char **tokens = NULL;
    
    c = cmd_del_spaces(c);
    c = mx_without_slash(c, NULL, 0, 0);
    main_c = strndup(c, strcspn(c, " \0"));
    if (no_buf(c, 0, 0) == 1) {
        tokens = mx_streams_cd(c, st, 64, main_c);
        if (mx_strcmp(main_c, "alias") == 0)
            st->status = mx_builtin_alias(st, tokens, NULL, NULL);
        else
            st->status = mx_streams(st, tokens, (t_app *)term->app);
    }
    else {
        tokens = midl_pars(st, c, 0, 64);
        st->status = mx_conveer(st, tokens, term);
    }
    return st->status;
}
