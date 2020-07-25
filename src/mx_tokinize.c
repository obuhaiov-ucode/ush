#include "ush.h"

void mx_tokinize(t_config* term, t_hist **hist, char *tmp) {
    char *token = strtok(tmp, "\t\t");

    for (int i = 0; token != NULL; i++, term->entry++) {
        hist[i]->line = mx_strdup(token);
        hist[i]->len = strlen(hist[i]->line);
        token = strtok(NULL, "\t\t");
    }
    free(token);
    free(tmp);
    term->total = term->entry;
}
