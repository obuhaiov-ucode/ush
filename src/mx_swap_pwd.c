#include "ush.h"

static void swapper(char *ch, t_app *app) {
    free(app->old_pwd_p);
    app->old_pwd_p = mx_strdup(app->pwd_p);
    free(app->old_pwd_l);
    app->old_pwd_l = mx_strdup(app->pwd_l);
    free(app->pwd_l);
    app->pwd_l = mx_strdup(ch);
    app->pwd_p = getwd(NULL);
    setenv("PWD", app->pwd_l, 1);
    mx_strdel(&ch);
    app->home = mx_strdup(getenv("HOME"));
    setenv("PWD", app->pwd_l, 1);
}

int mx_swap_pwd (char *ch, char *argv[], t_app *app, int *flag) {
    free(flag);
    if (ch) {
        if (chdir(ch) < 0) {
            fprintf(stderr,
                    "cd: no such file or directory: %s\n", argv[app->cur_arg]);
            return -1;
        }
        swapper(ch, app);
        return 0;
    }
    else
        return -1;
}

