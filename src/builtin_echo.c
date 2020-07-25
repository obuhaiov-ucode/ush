#include "ush.h"

static void switch_flags(char *argv[], t_app *app) {
    if (argv[1] == NULL || argv[1][0] != '-') {
        app->echo_start_of_file = 1;
    }
    else {
        for (int i = 1; argv[i] != NULL && argv[i][0] == '-'; i++) {
            for (unsigned int j = 1; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'n')
                    app->echo_flag_n = 1;
                else if (argv[i][j] == 'e')
                    app->echo_flag_E = 0;
                else if (argv[i][j] == 'E')
                    app->echo_flag_E = 1;
                else {
                    app->echo_start_of_file = i;
                    return;
                }
                
            }
            app->echo_start_of_file = i + 1;
        }
    }
}

static void del_first(t_cmd *cmd, char *argv[], int len_first, int len_last) {
    char *buf = NULL;

    if(cmd->argc == 2) {
        if ((argv[1][0] == '\"' && argv[1][len_first - 1] == '\"')
          || (argv[1][0] == '\'' && argv[1][len_first - 1] == '\'')) {
            buf = strndup(&argv[1][1], len_first - 2);
            mx_free_str(argv[1], buf);
       }
    }
    else if (cmd->argc > 2 ) {
        if ((argv[1][0] == '\"' && argv[cmd->argc - 1][len_last - 1] == '\"') 
          || (argv[1][0] == '\'' && argv[cmd->argc - 1][len_last] == '\'')) {
          buf = strndup(&argv[1][1], mx_strlen(argv[1]) - 1);
          mx_free_str(argv[1], buf);
          buf = strndup(argv[cmd->argc - 1], len_last - 1);
          mx_free_str(argv[cmd->argc - 1], buf);
        }
    }  
}

static void cheсk_all_quotes(char *argv[], t_app *app) {
    char *buf = NULL;

    for (int i = app->echo_start_of_file; argv[i] != NULL; i++) {
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

static void cheсk_first_quotes(t_cmd *cmd, char *argv[], t_app *app) {
    app->echo_single_quotes = 0;
    app->echo_double_quotes = 0;
    int len_first = mx_strlen(argv[1]);
    int len_last_argv = cmd->argc > 1 ? mx_strlen(argv[cmd->argc - 1]) : 0;

    if((argv[1][0] == '\'') || (argv[1][len_first - 1] == '\''))
      app->echo_single_quotes = 1;
    if((argv[1][0] == '\"') || (argv[1][len_first - 1] == '\''))
      app->echo_double_quotes = 1;
    if(!app->echo_single_quotes && !app->echo_double_quotes)
      app->echo_without_qoutes = 1;

    del_first(cmd, argv, len_first, len_last_argv);
    app->echo_flag_n = 0;
    app->echo_flag_E = 0;
    app->echo_start_of_file = 0;
    switch_flags(argv, app);
    cheсk_all_quotes(argv, app);
}

int mx_echo_builtin(char *argv[], t_app *app, t_cmd *cmd) {
    char *checked_argv = NULL;

    if(cmd->argc > 1) {
    cheсk_first_quotes(cmd, argv, app);
        for (int i = app->echo_start_of_file; argv[i] != NULL; i++) {
            if(app->echo_flag_E )
                write(1, argv[i], mx_strlen(argv[i]));
            else
                checked_argv = mx_control_chars(argv[i]);
                write(1, checked_argv, mx_strlen(checked_argv));
                mx_strdel(&checked_argv);
            if(argv[i+1])
                write(1, " ", 1);
            }
    //   if(!app->echo_flag_n)
          write(1, "\n", 1);
    }
    if(!app->echo_flag_n)
        write(1, "\n", 1);
    return EXIT_SUCCESS;
}
