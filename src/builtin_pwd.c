#include "ush.h"

static bool switch_flags(char *argv[], t_app *pwd) {
        for (int i = 1; argv[i] != NULL; i++) {
            if ((strcmp(argv[i], "--") == 0 && argv[i + 1]) ||
                (strcmp(argv[i], "-") == 0 && argv[i + 1]) ||
                    argv[i][0] != '-') {
                fprintf(stderr, "pwd: too many arguments\n"); //todo check \n
                return false;
            }
            for (unsigned int j = 1; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'P')
                    pwd->flag_p = 1;
                else if ((argv[i][j] != 'P' && argv[i][j] != 'L'
                    && argv[i][j] != '-') || (argv[i][j] == '-' && j == 2)) {
                    fprintf(stderr, "pwd: bad option: -%c\n", argv[i][j]);//todo check \n
                    return false;
                }
            }
        }
        return true;
}
static void check_last_simbols(t_app *pwd) {
    int dot = mx_strlen(pwd->pwd_l) -1; 
    int slesh = dot - 1;
    char *buf = NULL;

    if (pwd->pwd_l[slesh] == '/' && pwd->pwd_l[dot] == '.' ) {
        buf = mx_strndup(pwd->pwd_l, slesh);
        free(pwd->pwd_l);
        pwd->pwd_l = mx_strdup(buf);
        free(buf);
    }
}

int mx_pwd_builtin(char *argv[], t_app *pwd) {
    pwd->flag_p = 0;

    if(switch_flags(argv,pwd)) {
        check_last_simbols(pwd);
    if (pwd->flag_p) {
        printf("%s\n", pwd->pwd_p);
    }
    else if (!pwd->flag_p) {
        printf("%s\n", pwd->pwd_l);
        }
    else
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;

}
