#include "ush.h"

static char *get_back_dir_l(t_app *app) {
    char * link_path = NULL;
    char ** split_path = mx_strsplit(app->pwd_l, '/');
    int sum_strlen = 0;
    app->dot_dir = app->dd_slesh ? app->dot_dir : app->dot_dir - 1;

    if (mx_arr_len(split_path) <= app->dot_dir) {
        mx_del_strarr(&split_path);
        return NULL;
    }
    else if (app->dot_dir != 0) {
        for (int i = mx_arr_len(split_path) - app->dot_dir;
             split_path[i] != NULL; i++) {
            sum_strlen += strlen(split_path[i]);
        }
        sum_strlen += app->dot_dir;
        link_path = strndup(app->pwd_l, strlen(app->pwd_l) - sum_strlen);
        mx_del_strarr(&split_path);
    }
    return link_path;
}

static char *standart_argv(char *argv[], t_app *app) {
    char *ch = NULL;

    if (!mx_strcmp(argv[app->cur_arg], "/")
          || !mx_strcmp(argv[app->cur_arg],"/."))
            ch = mx_strdup("/");
    else {
        if (argv[app->cur_arg][0] == '/')
            ch = mx_strdup(argv[app->cur_arg]);
        else {
            ch = mx_strjoin(app->pwd_l, "/");
            ch = mx_strjoin(ch, argv[app->cur_arg]);
            }
        }
    return ch;
}

static char *check_path(char *argv[], t_app *app) {
    char * ch = NULL;
    
    if (argv[app->cur_arg][0] == '.'
        && mx_is_dot(argv[app->cur_arg], app) == 0) {
        ch = get_back_dir_l(app);
        ch = ch == NULL ? mx_strdup("/") : ch;
    }
    else if (app->in_pwd && mx_strcmp(argv[app->cur_arg],"/.") != 0) {
        ch = strndup(app->pwd_l,
                strlen(app->pwd_l) - strlen(argv[app->cur_arg - 1]));
        ch = mx_strjoin(ch, argv[app->cur_arg]);
    }
    else if (argv[app->cur_arg] && argv[app->cur_arg][0] != '.') {
        ch = standart_argv(argv, app);
    }
    return ch;
}

int mx_cd_l(char *argv[], t_app *app, int *flag) {
    char *ch = NULL;
     
    if(!mx_strcmp(argv[app->cur_arg], ".") && !argv[app->cur_arg + 1])
        ch = mx_strdup(app->pwd_l);
    else if (!mx_strcmp(argv[app->cur_arg], "-")) {
        if ((mx_is_link(app->old_pwd_l) == 1 && flag[0] == 1)) {
            fprintf(stderr, "cd: not a directory: %s\n", app->old_pwd_l);
            return - 1;
        }
        ch = app->old_pwd_l ? mx_strdup(app->old_pwd_l) : mx_strdup(app->pwd_l);
    }
    else
        ch = check_path(argv, app);
    if (app->in_pwd && mx_is_link(ch) == 1 && flag[0] == 1) {
        fprintf(stderr, "cd: not a directory: %s\n", getwd(argv[app->cur_arg]));
        free(flag);
        mx_strdel(&ch);
        return -1;
    }
    if (mx_swap_pwd(ch, argv, app, flag) == 0)
        return 0;
    return -1;
}
