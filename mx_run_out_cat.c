#include "ush.h"

void mx_run_out_cat(t_st *st, char **tok) {
    close(st->cfd1[0]);
    close(st->cfd0[1]);
    close(st->cfd0[0]);

    if (st->cfd1[1] != STDOUT_FILENO) {
        if (dup2(st->cfd1[1], STDOUT_FILENO) != STDOUT_FILENO)
            perror("ush: ");
        close(st->cfd1[0]);
    }
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    execvp(tok[0], tok);
}
