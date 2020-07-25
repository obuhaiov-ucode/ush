#include "ush.h"

void mx_check_in_pwd(char *our, char *argv[], t_app *app) {
    if (our != NULL && mx_strcmp(argv[app->cur_arg], our) == 0)
        app->in_pwd = 1;
    else
        app->in_pwd = 0;
}

