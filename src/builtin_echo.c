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

void check_sound(char *out, t_app *app) {
    for (int i = 0; out[i] != '\0'; i++)
        if (out[i] == '\a')
            app->echo_only_sound = 1;

}

void echo_print_new_line(t_app *app, char *argv[]) {
    char c = 7;
    
    if(app->echo_only_sound)
        write(1, &c, 1);
    if(!app->echo_flag_n)
        write(1, "\n", 1);
    if(app->echo_flag_n && (argv[app->st] 
        && mx_strcmp(argv[app->st], "\\a") != 0)) {
            write(2,argv[app->st], mx_strlen(argv[app->st]));
        write(1, "\x1b[30m\x1b[107m", strlen("\x1b[30m\x1b[107m"));
        write(1, "%", 1);
        write(1, "\x1b[0m", strlen("\x1b[0m"));
        write(1, "\n", 1);
    }
}

int mx_echo_builtin(char *argv[], t_app *app) {
    char *checked_argv = NULL;
 
    switch_flags(argv, app);
    for (int i = app->st; argv[i] != NULL; i++) {
        if(app->echo_flag_E )
            write(1, argv[i], mx_strlen(argv[i]));
        else {
            checked_argv = mx_control_chars(argv[i]);
            write(1, checked_argv, mx_strlen(checked_argv));
            mx_strdel(&checked_argv);
        }
        if(argv[i+1])
            write(1, " ", 1);
        }
    echo_print_new_line(app, argv);
    return EXIT_SUCCESS;
}
