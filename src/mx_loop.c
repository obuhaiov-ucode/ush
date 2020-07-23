#include "ush.h"

static void run_cat(char *cmd, int i, char **tok) {
    pid_t pid = 0;

    dup2(0, STDIN_FILENO);
    dup2(1, STDOUT_FILENO);
    if ((pid = fork()) < 0)
        perror("ush: ");
    if (pid == 0) {
        tok = malloc(sizeof(char *) * 3);
        tok[0] = strdup("/bin/cat");
        i = strcspn(cmd, " \0");
        if (i == mx_strlen(cmd))
            tok[1] = NULL;
        else
            tok[1] = strndup(&cmd[i + 1], strcspn(&cmd[i], "\0"));
        tok[2] = NULL;
        execvp(tok[0], tok);
    }
    else
        wait(&pid);
}

void mx_loop(char *cmd, t_config* term, t_st *st) {
    if (cmd != NULL && mx_check_cmd(cmd, 0)) {
        cmd = mx_shlvl_check(cmd, 0, NULL);
        st->cmd = cmd;
        // if (mx_check_quotes(st->cmd) == 1) {
        //     write(2, "Odd number of quotes.\n", 22);
        //     exit(1);
        // }
        if (strstr(cmd, "cat") && (int)strcspn(cmd, "|") == mx_strlen(cmd))
            run_cat(cmd, 0, NULL);
        else {
            st->commands = mx_split_line(st->cmd, 64, 0, 0);
            st->status = mx_simple_commands(st, st->commands, term);
            //mx_del_strarr(&st->commands);
        }
    } 
    fflush(stdin);
    fflush(stdout);
}
