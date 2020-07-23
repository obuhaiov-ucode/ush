#include "ush.h"

static void bzero_for_flags(t_app *app) {
    app->echo_flag_n = 0;
    app->echo_flag_E = 0;
    app->echo_start_of_file = 0;
}

// static bool check_sound(char *out) {
//     for (int i = 0; out[i] != '\0'; i++)
//         if (out[i] != '\a')
//             return false;
//     return true;
// }
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


static void print_new_line(t_app *app) {
    if(!app->echo_flag_n) {
        if(app->echo_only_sound)
            return;
        // else if (isatty(1))
        //     printf("\x1b[0;47;30m%%\x1b[0m\n");
    }
    else 
        mx_printstr("\n");

}

// static void cheсk_quotes(char *argv[]) {
//     write(2, "check1\n", 6);
//     char *buf = NULL;
//     int arr_len = mx_arr_len(argv) > 1 ? mx_arr_len(argv) - 1 : 1;
//     fprintf(stderr, "%d\n", arr_len);
//     write(2, "check2\n", 6);
//     int len_last_str = mx_strlen(argv[arr_len]);
//     write(2, argv[1], mx_strlen(argv[1]));

//     // || argv[arr_len][len_last_str - 1] == '\"')

//     if(argv[1] && (argv[1][0] == '\"') {
//         write(2, "check3\n", 6);
//         buf = mx_strndup(&argv[1][1], argv[arr_len][len_last_str - 2] == '"');
//         mx_strdel(&argv[1]);
//         argv[1] = mx_strdup(buf);
//         mx_strdel(&buf);
//         buf = mx_strndup(argv[arr_len], argv[arr_len][len_last_str - 2]);
//         mx_strdel(&argv[arr_len]);
//         mx_strdel(&buf);
//     }
//     else
//         return;    
// }  
      

int mx_echo_builtin(char *argv[], t_app *app) {
    //write(2, "here1\n", 6);
    char *checked_argv = NULL;
    //  printf("argv[i] = %s\n", argv[app->echo_start_of_file]);
    //cheсk_quotes(argv);
   // write(2, "here2\n", 6);
    switch_flags(argv, app);
   // write(2, "here2\n", 6);
//    for (int j = 0; argv[j] != NULL; j++) {
//        write(2, argv[j], mx_strlen(argv[j]));
//         write (2, "  ", 1);
//    }
//     write (2, "the end\n", 8);
//write(1, "\n", 1);
    if (argv[app->echo_start_of_file] != NULL) {

            for (int i = app->echo_start_of_file; argv[i] != NULL; i++) {
                // write(2, argv[i], mx_strlen(argv[i]));       
                // write (2, "\n", 1);
                if(app->echo_flag_E)
                    write(1, argv[i], mx_strlen(argv[i]));
                else {
                    checked_argv = mx_control_chars(argv[i]);
                    write(1, checked_argv, mx_strlen(checked_argv));
                    mx_strdel(&checked_argv);
                    //app->echo_only_sound = check_sound(checked_argv);
                }
                if(argv[i+1])
                    write(1, " ", 1);
            }
    }
    //
    print_new_line(app);
    write(1, "\n", 1);
    return EXIT_SUCCESS;
}
