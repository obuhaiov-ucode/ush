#include "ush.h"

static char *get_back_dir_p(t_app *app) {
    char * real_path = NULL;
    char ** split_path = mx_strsplit(app->pwd_l, '/');
    int sum_strlen = 0;

    app->dot_dir = !app->dd_slesh ? app->dot_dir - 1 : app->dot_dir;
    if (mx_arr_len(split_path) <= app->dot_dir) {
        mx_del_strarr(&split_path);
        return NULL;
    }
    else if (app->dot_dir != 0) {
        for (int i = mx_arr_len(split_path) - app->dot_dir;
             split_path[i] != NULL; i++) {
            sum_strlen += mx_strlen(split_path[i]);
        }
        sum_strlen += app->dot_dir;
        real_path = strndup(app->pwd_p, strlen(app->pwd_p) - sum_strlen);
        mx_del_strarr(&split_path);
    }
    return real_path;
}

static char *check_path(char *argv[], t_app *app) {
    char *ch = NULL;

    if (!mx_strcmp(argv[app->cur_arg], ".") && !argv[app->cur_arg + 1])
        ch = mx_strdup(app->pwd_p);
    else if (app->in_pwd) {
        if (!mx_strcmp(argv[app->cur_arg], "/tmp"))
            ch = mx_strdup(argv[app->cur_arg]);
        else {
            ch = strndup(app->pwd_l, strlen(app->pwd_l)
                         - strlen(argv[app->cur_arg - 1]));
            ch = mx_strjoin(ch, argv[app->cur_arg]);
        }
    }
    else if (argv[app->cur_arg] && argv[app->cur_arg][0] != '.') 
        ch = mx_strdup(argv[app->cur_arg]);
    else if (argv[app->cur_arg][0] == '.'
             && mx_is_dot(argv[app->cur_arg], app) == 0) {
        ch = get_back_dir_p(app);
        ch = ch == NULL ? mx_strdup("/") : ch;
    }
    return ch;
}

static int check_other_variant(char *argv[], t_app *app, int *flag, char *ch) {
    if (app->in_pwd && mx_is_link(ch) == 1 && flag[0] == 1) {
        free(flag);
        mx_strdel(&ch);
        fprintf(stderr, "cd: not a directory: %s\n", getwd(argv[app->cur_arg]));
        return -1;
    }
    if (mx_swap_pwd(ch, argv, app, flag) == 0) {
        free(app->pwd_l);
        app->pwd_l = mx_strdup(app->pwd_p);
        return 0;
    }
    return -1;
}

int mx_cd_p(char *argv[], t_app *app, int *flag) {
    char *ch = NULL;
    int res = -1;

    if (mx_strcmp(argv[app->cur_arg], "-")  == 0) {
        if ((mx_is_link(app->old_pwd_l) == 1 && flag[0] == 1)) {
            fprintf(stderr, "cd: not a directory: %s\n", app->old_pwd_l);
            free(flag);
            return -1;
        }
        ch = app->old_pwd_p ? mx_strdup(app->old_pwd_p) : mx_strdup(app->pwd_p);
    }
    else
        ch = check_path(argv, app);

   
    res = check_other_variant(argv, app, flag, ch);
    return res;
}

