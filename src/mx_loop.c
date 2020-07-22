#include "ush.h"

void mx_loop(char *cmd, t_config* term, t_st *st) {
    //printf("%s\n", cmd);
    if (cmd != NULL && mx_check_cmd(cmd, 0)) {
        cmd = mx_shlvl_check(cmd, 0, NULL);
        st->cmd = cmd;
        if (mx_check_quotes(st->cmd) == 1) {
            write(2, "Odd number of quotes.\n", 22);
            exit(1);
        }
        st->commands = mx_split_line(st->cmd, 64, 0, 0);
        st->status = mx_simple_commands(st, st->commands, term);
        mx_del_strarr(&st->commands);
    } 
    fflush(stdin);
    fflush(stdout);
}
