#include "ush.h"

static void switch_flags(char *argv[], t_app *app) {
    if (argv[1] == NULL || argv[1][0] != '-') 
        app->st = 1;
    else {
        for (int i = 1; argv[i] != NULL && argv[i][0] == '-'; i++) {
            for (int j = 1; j < mx_strlen(argv[i]); j++) {
                if (argv[i][j] == 'n') 
                    app->echo_flag_n = 1;
                else if (argv[i][j] == 'e') 
                    app->echo_flag_E = 0;
                else if (argv[i][j] == 'E')
                    app->echo_flag_E = 1;
                else {
                    app->st = i + 1;
                    return;
                }
            }
            app->st = i + 1;
        }
    }
}

static void cheсk_all_quotes(char *argv[], t_app *app) {
    char *buf = NULL;

    for (int i = app->st; argv[i] != NULL; i++) {
        for (int j = 0; j < mx_strlen(argv[i]); j++) {
            if(app->echo_single_quotes || app->echo_without_qoutes){
                if(argv[i][j] == '\'') {
                    buf = mx_replace_substr(argv[i], "\'", "");
                    argv[i] = mx_free_str(argv[i], buf);
                }
            }
            else if(app->echo_double_quotes || app->echo_without_qoutes) {
                if(argv[i][j] == '\"') {
                    buf = mx_replace_substr(argv[i], "\"", "");
                    argv[i] = mx_free_str(argv[i], buf);
                }
            }
        }
    }
}

static void del_first(char *argv[], int lf, t_cmd *cmd, t_app *app) {
    char *buf = NULL;
    int ll = cmd->argc > 1 ? mx_strlen(argv[cmd->argc - 1]) : 0;

    if(argv[app->st] && !argv[app->st + 1]) {
        if ((argv[app->st][0] == '\"' && argv[app->st][lf - 1] == '\"')
            || (argv[app->st][0] == '\'' 
            && argv[app->st][lf - 1] == '\'')) {
            buf = strndup(&argv[app->st][1], lf - 2);
            mx_free_str(argv[app->st], buf);
       }
    }
    else if (argv[app->st + 1]) {
        if ((argv[app->st][0] == '\"' && argv[cmd->argc - 1][ll - 1] == '\"') 
            || (argv[app->st][0] == '\'' && argv[cmd->argc - 1][ll] == '\'')) {
            buf = mx_strdup(&argv[app->st][1]);      
            argv[app->st] = mx_free_str(argv[app->st], buf);
            buf = strndup(argv[cmd->argc - 1], ll - 1);
            argv[cmd->argc - 1] = mx_free_str(argv[cmd->argc - 1], buf);
        }
    }  
}

static void cheсk_first_quotes(t_cmd *cmd, char *argv[], t_app *app) {
    app->echo_flag_n = 0;
    app->echo_flag_E = 0;
    app->st = 1;
    switch_flags(argv, app);
     if(argv[app->st]) {
    app->echo_single_quotes = 0;
    app->echo_double_quotes = 0;
    int lf = mx_strlen(argv[1]);

    if((argv[app->st][0] == '\'') 
        || (argv[app->st][lf - 1] == '\''))
        app->echo_single_quotes = 1;
    if((argv[app->st][0] == '\"') || (argv[app->st][lf - 1] == '\''))
        app->echo_double_quotes = 1;
    if(!app->echo_single_quotes && !app->echo_double_quotes)
        app->echo_without_qoutes = 1;
     
    del_first(argv, lf, cmd, app);
    cheсk_all_quotes(argv, app);
    }
}

int mx_echo_builtin(char *argv[], t_app *app, t_cmd *cmd) {
    char *checked_argv = NULL;
 
    cheсk_first_quotes(cmd, argv, app);
        for (int i = app->st; argv[i] != NULL; i++) {
            if(app->echo_flag_E )
                write(1, argv[i], mx_strlen(argv[i])); // check without shesh; check_sound
            else {
                checked_argv = mx_control_chars(argv[i]);
                write(1, checked_argv, mx_strlen(checked_argv));
                mx_strdel(&checked_argv);
            }
            if(argv[i+1])
                write(1, " ", 1);
            }
    if(!app->echo_flag_n)
        write(1, "\n", 1);
    if(app->echo_flag_n && argv[app->st]) {
        write(1, "\x1b[30m\x1b[107m", strlen("\x1b[30m\x1b[107m"));
        write(1, "%", 1);
        write(1, "\x1b[0m", strlen("\x1b[0m"));
        write(1, "\n", 1);
    }
    return EXIT_SUCCESS;
}
