#include "ush.h"

static void piped_print(t_st *st) {
    int n = mx_strlen(st->buf[st->pipe]);

    if (st->buf[st->pipe] != NULL)
        write(1, st->buf[st->pipe], n);
    if (st->fbuf[st->pipe] != NULL) {    
        n = mx_strlen(st->fbuf[st->pipe]);
        write(1, st->fbuf[st->pipe], n);
    }
}

static int piped_parent(t_st *st, int pipe) {
    int n = 0;
    char line[8192];

    memset(line, 0, 8192);
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

static int piped_run(t_st *st, char **tokens, int i, t_config* term) {
    pid_t pid = 0;

    st->fd0[0] = 0;
    st->fd0[1] = 0;
    st->fd1[0] = 0;
    st->fd1[1] = 0;
    if (pipe(st->fd0) < 0 || pipe(st->fd1) < 0)
        perror("ush: ");
    if ((pid = fork()) < 0)
        perror("ush: ");
    if (pid == 0)
        mx_piped_child(st, tokens, term);
    else    
        st->status = piped_parent(st, i);
    if (!WIFEXITED(st->status) && !WIFSIGNALED(st->status))
        waitpid(pid, &st->status, WUNTRACED);
    st->status = WEXITSTATUS(st->status);
    wait(&pid);
    return st->status;
}

int mx_conveer(t_st *st, char **tokens, t_config* term) {
    char ***tok = mx_streams_get(st, tokens);
    int i = 0;

    for (i = 0; tok[i] != NULL; i++) {
        st->status = piped_run(st, tok[i], i, term);
        if (mx_strcmp(tok[i][0], "echo") != 0) {
            st->fbuf[i] = mx_file_input(st, i);
        }
        mx_file_output(st, i);
    }
    if (!st->out[st->pipe] && !st->end[st->pipe])
        piped_print(st);
    return st->status;
}
