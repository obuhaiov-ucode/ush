#include "ush.h"

int mx_status_check(char **tokens, t_app *app) {
    if (mx_strcmp(tokens[0], "echo") == 0
        && tokens[1][0] == '$' && tokens[1][1] == '?') {
        mx_printint(app->status);
        write(1, "\n", 1);
        return 0;
    }
    return 1;
}
