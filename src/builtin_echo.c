#include "ush.h"

static void bzero_for_flags(t_app *app) {
    app->echo_flag_n = 0;
    app->echo_flag_E = 0;
    app->echo_start_of_file = 0;
}

static void switch_flags(char *argv[], t_app *app) {
    bzero_for_flags(app);
    if (argv[1] == NULL || argv[1][0] != '-') {
        app->echo_start_of_file = 1;
         //write(2, argv[app->echo_start_of_file], mx_strlen(argv[app->echo_start_of_file]));
    }
    else {
       //  write(2, "else \n", 6);
        for (int i = 1; argv[i] != NULL && argv[i][0] == '-'; i++) {
          //  write(2,"after 1 for\n", 13);
            for (unsigned int j = 1; j < strlen(argv[i]); j++) {
               // write(2, "hello\n", 6);
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
           // write(2, "came back\n", 6);
        }
    }
    //write(2, argv[app->echo_start_of_file], mx_strlen(argv[app->echo_start_of_file]));
}

static char *print_new_line(char *res, t_app *app) {
    if (app->echo_flag_n) {
        if (res)
            res = mx_strjoin(res, "%\n");
    }
    else if (res)
        res = mx_strjoin(res, "\n");
    else 
        res = mx_strjoin(res, "\n");
    return res;
}

static void cheсk_quotes(char *argv[], t_app *app) {
    char *buf = NULL;
    int arr_len = mx_arr_len(argv) - 1;
    int len_first_str = 0;
    int len_last_str = 0;
   
    if (arr_len > 0) {
        len_first_str = mx_strlen(argv[1]) - 1;
        len_last_str = mx_strlen(argv[arr_len]);
        if(argv[app->echo_start_of_file] && !argv[app->echo_start_of_file + 1]) {
            if((argv[1][0] == '\"' &&  argv[1][len_first_str] == '\"') 
                || (argv[1][0] == '\'' &&  argv[1][len_first_str] == '\'')) {
                buf = mx_strndup(&argv[1][1], len_first_str - 1);
                mx_strdel(&argv[1]);
                argv[1] = mx_strdup(buf);
                mx_strdel(&buf);
            }
        }
        else if (argv[app->echo_start_of_file + 1]) {
            if((argv[1][0] == '\"' || argv[1][len_first_str] == '\"')
                || (argv[1][0] == '\'' && argv[arr_len][len_last_str] == '\'')) {
                buf = mx_strndup(&argv[1][1], len_first_str);
                mx_strdel(&argv[1]);
                argv[1] = mx_strdup(buf);
                mx_strdel(&buf);
                buf = mx_strndup(argv[arr_len], len_last_str - 1);
                mx_strdel(&argv[arr_len]);
                argv[arr_len] = mx_strdup(buf);
                mx_strdel(&buf);
            }
        }
    }
   
    
        return;    
}       

char *mx_echo_builtin(char *argv[], t_app *app) {
    char *res = NULL;
    char *checked_argv = NULL;
    switch_flags(argv, app);
    // res = mx_strdup(argv[app->echo_start_of_file]);
   cheсk_quotes(argv, app);
   // write(2, mx_itoa(app->echo_start_of_file), mx_strlen(mx_itoa(app->echo_start_of_file)));
    if (argv[app->echo_start_of_file] != NULL) {
            for (int i = app->echo_start_of_file; argv[i] != NULL; i++) {
                if(app->echo_flag_E)
                    res = mx_strjoin(res, argv[i]);
                else {
                    checked_argv = mx_control_chars(argv[i]);
                    res = mx_strjoin(res, argv[i]);
                    mx_strdel(&checked_argv);
                }
                if(argv[i+1])
                    res = mx_strjoin(res, " ");
            }
    }
    res = print_new_line(res, app);
    //printf("1 = %s\n", res);
    res = mx_without_slash(res, NULL, 0, 0);
    //printf("2 = %s\n", res);
    return res;
}


