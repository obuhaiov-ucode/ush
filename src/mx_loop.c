#include "ush.h"

// static void shlvl_check() {
//     tmp = getenv("SHLVL");
//     if (tmp == NULL)
//         setenv("SHLVL", "1", 1);
//     else {
//         n = atoi(tmp);
//         n++;
//         sprintf(tmp, "%d", n);
//         setenv("SHLVL", tmp, 1);
//     }
// }

char *mx_shlvl_check(char *tok, int n, char *tmp) {
    tmp = getenv("SHLVL");
    if (mx_strcmp(tok, "./ush") == 0 && tmp != NULL) {
        n = atoi(tmp) + 1;
        tmp = mx_itoa(n);
        tmp = mx_strjoin("unset SHLVL ; export SHLVL=", tmp);
        //free(tok);
        return tmp;
    }
    else if (tmp == NULL)
        setenv("SHLVL", "1", 1);
    return tok;
}

void mx_loop(char *cmd, t_config* term, t_st *st) {

    cmd = mx_shlvl_check(cmd, 0, NULL);
    st->cmd = cmd;
    //printf("%s\n", cmd);
    if (mx_check_quotes(st->cmd) == 1) {
        write(2, "Odd number of quotes.\n", 22);
        exit(1);
    }
    st->commands = mx_split_line(st->cmd, 64, 0, 0);
    st->status = mx_simple_commands(st, st->commands, term);
    fflush(stdin);
    fflush(stdout);
}
