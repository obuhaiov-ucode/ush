#include "ush.h"

static bool comparator(const char *name) {
    bool is_dir = 0;

    if (strcmp(name, ".") == 0)
        is_dir = 1;
    if (strcmp(name, "..") == 0)
        is_dir = 1;
    return is_dir;
}

static int count_processor(DIR *mydir) {
    struct dirent *myfile;
    int count = 0;

    while((myfile = readdir(mydir)) != NULL) {
        if (myfile->d_name[0] != '.' && comparator(myfile->d_name) == 0)
            count++;
    }
    return count;
    printf("%d\n", count);
}

static void count_commands(t_config *term) {
    char *cmd[3] = {"/usr/bin", "/bin", "/sbin"};
    DIR *mydir;

    for (int j = 0; j < 3; j++) {
        if ((mydir = opendir(cmd[j])) != NULL)
            term->count += count_processor(mydir);
        closedir(mydir);
    }
}

static void add_commands(t_config *term, int i) {
    char *cmd[3] = {"exit", "history", "help"};

    for (int j = 0; j < 3; j++, i++)
        term->command[i] = mx_strdup(cmd[j]);
}

void mx_get_commands(t_config *term) {
    char *cmd[3] = {"/usr/bin", "/bin", "/sbin"};
    struct dirent *dirptr;
    DIR *mydir;
    int i = 0;
    int j = 0;

    count_commands(term);
    term->command = (char **)malloc(sizeof(char *) * (term->count + 3));
    for (j = 0; j < 3; j++) {
        if ((mydir = opendir(cmd[j])) != NULL) {
            while((dirptr = readdir(mydir)) != NULL) {
                if (dirptr->d_name[0] != '.'
                    && comparator(dirptr->d_name) == 0)
                    term->command[i++] = mx_strdup(dirptr->d_name);
            }
        }
        closedir(mydir);
    }
    add_commands(term, i);
}
