#include "ush.h"

void mx_choose_way(t_config* term, t_hist **hist) {
    if (!strncmp("clear", term->str, 5))
        mx_clear(term->str);
    else if (!strncmp("history", term->str, 7))
        mx_history(term->str);
    else if (!strncmp("help", term->str, 4))
        mx_help(term->str);
    else
        mx_loop(term->str, term->str_len, term, (t_st *)term->st);
    if (hist[0]->line != NULL) {
        for (int i = 0; i < term->entry; i++) {
            free(hist[i]->line);
            hist[i]->line = NULL;
            hist[i]->len = 0;
        }
    }
}
