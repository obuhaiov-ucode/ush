#include "ush.h"

static void out_print(t_st *st, FILE *f) {
    if (st->cbuf != NULL)
        fprintf(f, "%s", st->cbuf);
    if ((st->cout != 0 || st->cend != 0) && st->cin != 0)
        fprintf(f, "\n");
}

void mx_file_output_cat(t_st *st) {
    FILE *begin;
    FILE *end;

    for (int i = 0; i < st->cout; i++) {
        if ((begin = fopen(st->coutput[i], "w")) == NULL)
            perror("ush: ");
        out_print(st, begin);
        fclose(begin);
    }
    for (int i = 0; i < st->cend; i++) {
        if ((end = fopen(st->cendout[i], "a")) == NULL)
            perror("ush: ");
        out_print(st, end);
        fclose(end);
    }
}
