#include "ush.h"

static void init_redir(t_st *st) {
    st->cin = 0;
    st->cout = 0;
    st->cend = 0;
    st->cbuf = NULL;
    st->cfbuf = NULL;
    if (st->cbuf)
        mx_del_chararr(st->cbuf);
    if (st->cfbuf)
        mx_del_chararr(st->cfbuf);
    if (st->cinput)
        mx_del_strarr(&st->cinput);
    if (st->coutput)
        mx_del_strarr(&st->coutput);
    if (st->cendout)
        mx_del_strarr(&st->cendout);
}

static char **without_redir(t_st *st, char **tokens) {
    init_redir(st);
    if ((st->cin = mx_count_streams(tokens, '<', 0, 0)) > 0)
        tokens = mx_streams_cin(st, tokens, 0);
    if ((st->cout = mx_count_streams(tokens, '>', 0, 0)) > 0)
        tokens = mx_streams_cout(st, tokens, 0);
    if ((st->cend = mx_count_streams(tokens, '>', 0, 1)) > 0)
        tokens = mx_streams_cendout(st, tokens, 0);
    tokens = mx_weird_slash(tokens, NULL, st, NULL);
    return tokens;
}

static char **cat_pars(t_st *st, char *c, int k, int bufsize) {
    char **tokens = malloc(bufsize * sizeof(char*));

    for (int i = 0; c[i] != '\0'; i++) {
        if (c[i] == '|' || c[i] == '<' || c[i] == '>')
            tokens[k++] = strndup(&c[i], 1);
        else if (c[i] != ' ') {
            tokens[k++] = strndup(&c[i], strcspn(&c[i], " <>|"));
            i += strcspn(&c[i], " <>|") - 1;
        }
        tokens = mx_split_backup(tokens, bufsize, k);
        if (k >= bufsize)
            bufsize += 64;
    }
    tokens[k] = NULL;
    tokens = without_redir(st, tokens);
    return tokens;
}

static void run_cat(t_st *st, char *cmd, char **tok, pid_t pid) {
    char line[8192];

    tok = cat_pars(st, cmd, 0, 64);
    st->cfbuf = mx_file_input_cat(st);
    if (pipe(st->cfd0) < 0 || pipe(st->cfd1) < 0)
        perror("ush: ");
    if ((pid = fork()) < 0)
        perror("ush: ");
    if (pid == 0) {
        if (st->cin > 0 && (st->cout > 0 || st->cend > 0))
            mx_run_inout_cat(st, tok);
        else if (st->cin > 0)
            mx_run_in_cat(st, tok);
        else if (st->cout > 0 || st->cend > 0)
            mx_run_out_cat(st, tok);
        else
            execvp(tok[0], tok);
    }
    else
        st->status = mx_parent_cat(st, 0, pid, line);
}

void mx_loop(char *cmd, t_config* term, t_st *st) {
    //system("leaks -q ush");
    if (cmd != NULL && mx_check_cmd(cmd, 0)) {
        cmd = mx_shlvl_check(cmd, 0, NULL);
        if (cmd[0] != 39 && mx_check_quotes(cmd) == 1) {
            write(2, "Odd number of quotes.\n", 22);
            exit(1);
        }
        if (strstr(cmd, "cat") && (int)strcspn(cmd, "|") == mx_strlen(cmd))
            run_cat(st, cmd, NULL, 0);
        else {
            st->cmd = cmd;
            st->commands = mx_split_line(st->cmd, 64, 0, 0);
            st->status = mx_simple_commands(st, st->commands, term);
            //mx_del_strarr(&st->commands);
            //mx_del_chararr(st->cmd);
        }
    }
    fflush(stdin);
    fflush(stdout);
}
