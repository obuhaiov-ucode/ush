#include "ush.h"

static void out_print(t_st *st, FILE *f, char *tmp) {
    //int i = 0;
    (void)tmp;
    if (st->cfbuf != NULL)
        fprintf(f, "%s\n", st->cfbuf);

    if (st->cbuf != NULL) {
        //tmp = mx_strndup(st->cbuf, i);
        fprintf(f, "%s\n", st->cbuf);
        //mx_del_chararr(tmp);
    }
}

void mx_file_output_cat(t_st *st) {
    FILE *begin;
    FILE *end;

    for (int i = 0; i < st->cout; i++) {
        if ((begin = fopen(st->coutput[i], "w")) == NULL)
            perror("ush: ");
        out_print(st, begin, NULL);
        fclose(begin);
        //for (int i = 0; st->coutput[i] != NULL; i++)
        //   printf("out = %d = %s\n", i, st->coutput[i]);
    }
    for (int i = 0; i < st->cend; i++) {
        if ((end = fopen(st->cendout[i], "a")) == NULL)
            perror("ush: ");
        out_print(st, end, NULL);
        fclose(end);
        //for (int i = 0; st->cendout[i] != NULL; i++)
        //    printf("end = %d = %s\n", i, st->cendout[i]);
    }
}
