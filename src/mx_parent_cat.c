#include "ush.h"

int mx_parent_cat(t_st *st, int n, pid_t pid, char line[8192]) {
    close(st->cfd0[0]);
    close(st->cfd1[1]);
    if (st->cin > 0)
        write(st->cfd0[1], st->cfbuf, mx_strlen(st->cfbuf));
    close(st->cfd0[1]);
    if (st->cout > 0 || st->cend > 0) {
        memset(line, 0, 8192);
        n = read(st->cfd1[0], line, 8192);
        n = mx_strlen(line);
        line[n] = '\0';
        st->cbuf = mx_strndup(line, n);
    }
    close(st->cfd1[0]);
    waitpid(pid, &st->status, WUNTRACED);
    wait(&pid);
    st->status = WEXITSTATUS(st->status);
    mx_file_output_cat(st);
    if (st->cout == 0 && st->cend == 0 && st->cin != 0)
        write(1, "\n", 1);
    return st->status;
}
