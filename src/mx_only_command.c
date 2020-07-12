#include "ush.h"

static int child(t_st *st, int pipe) {
    int n = 0;
    char line[8192];

    for (int i = 0; i < 8192; i++)
        line[i] = '\0';
    close(st->fd0[0]);
    close(st->fd1[1]);
    if (st->buf[pipe - 1] != NULL && pipe > 0)
        write(st->fd0[1], st->buf[pipe - 1], mx_strlen(st->buf[pipe - 1]));
    close(st->fd0[1]);
    if ((n = read(st->fd1[0], line, 8192)) < 0)
        perror("ush: ");
    close(st->fd1[0]);
    n = mx_strlen(line);
    line[n] = '\0';
    st->buf[pipe] = mx_strndup(line, n);
    return st->status;
}


int mx_only_command(t_st *st, char **tokens, t_app *app) {
    pid_t pid;

    if ((pid = fork()) < 0)
        perror("ush: ");
    if (pid > 0)
        st->status = piped_parent(st, i);
    else {
        signal(SIGTSTP, SIG_DFL);
        signal(SIGINT, SIG_DFL);
        signal(SIGSEGV, SIG_DFL);
        mx_piped_child(st, tokens, term);
    }
    return st->status;
}
