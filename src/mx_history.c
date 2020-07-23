#include "ush.h"

static void print_spaces(int i) {
    if (i < 9)
        write(1, " ", 1);
    if (i < 99)
        write(1, " ", 1);
    write(1, " ", 1);
}

static void tokenize(char tmp[]) {
    char *token = strtok(tmp, "\t");

    for (int i = 0; token != NULL; i++) {
        if (i != 0)
            write(1, "\r\n", 2);
        write(1, mx_itoa(i + 1), strlen(mx_itoa(i + 1)));
        print_spaces(i);
        write(1, token, strlen(token));
        token = strtok(NULL, "\t");
    }
    free(token);
}

void mx_history(char *str) {
    char tmp[1024];
    FILE *fp;

    if (!strcmp("history", str)) {
        if ((fp = fopen (".file.txt", "r"))) {
            fgets(tmp, 1024, (FILE*)fp);
            fclose(fp);
        }
        if (strlen(tmp))
            tokenize(tmp);
        write(1, "\r\n", 2);
    }
    else
        write(2, "\rush: history: too many arguments\r\n", 36);
}
