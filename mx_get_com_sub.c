#include "ush.h"

static int sub_child(t_st *st, char *midl, int *sub1, t_config* term) {
    close(sub1[0]);

    if (sub1[1] != STDOUT_FILENO) {
        if (dup2(sub1[1], STDOUT_FILENO) != STDOUT_FILENO)
            perror("ush: ");
        close(sub1[1]);
    }
    st->have_sub = true;
    st->stat_sub = mx_command_pars(st, midl, NULL, term);
    exit(st->stat_sub);
}

static char *sub_parent(t_st *st, char *cmd, int n) {
    char line[8192];

    memset(line, 0, 8192);
    close(st->sub1[1]);
    if ((n = read(st->sub1[0], line, 8192)) < 0)
        perror("ush: ");
    close(st->sub1[0]);
    n = mx_strlen(line);
    line[n - 1] = '\0';
    cmd = mx_strndup(line, n - 1);
    return cmd;
}

static char *sub_run(t_st *st, char *midl, char *cmd, t_config* term) {
    pid_t pid;

    if (pipe(st->sub1) < 0)
        perror("ush: ");
    if ((pid = fork()) < 0)
        perror("ush: ");
    if (pid == 0)
        st->stat_sub = sub_child(st, midl, st->sub1, term);
    else    
        cmd = sub_parent(st, cmd, 0);
    if (!WIFEXITED(st->status) && !WIFSIGNALED(st->status))
        waitpid(pid, &st->status, WUNTRACED);
    st->status = WEXITSTATUS(st->status);
    wait(&pid);
    return cmd;
}

static char *maybe_final(char *cmd, char *final) {
    char *tmp = NULL;

    tmp = mx_strjoin(cmd, final);
    free(final);
    free(cmd);
    return tmp;
}

char *mx_get_com_sub(t_config* term, char *begin, char *midl, char *final) {
    char *cmd = sub_run((t_st *)term->st, midl, NULL, term);
    char *tmp = NULL;

    if (begin != NULL) {
        tmp = mx_strjoin(begin, cmd);
        free(begin);
        free(cmd);
        if (final != NULL) {
            cmd = mx_strjoin(tmp, final);
            free(tmp);
            free(final);
        }
        else
            cmd = tmp;
    }
    else if (final != NULL)
        cmd = maybe_final(cmd, final);
    return cmd;
}
