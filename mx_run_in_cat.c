#include "ush.h"

void mx_run_in_cat(t_st *st, char **tok) {
    close(st->cfd0[1]);
    close(st->cfd1[1]);
    close(st->cfd1[0]);

    if (st->cfd0[0] != STDIN_FILENO) {
        if (dup2(st->cfd0[0], STDIN_FILENO) != STDIN_FILENO)
            perror("ush: ");
        close(st->cfd0[0]);
    }
    execvp(tok[0], tok);
}
