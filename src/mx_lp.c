#include "ush.h"

static void clean_up(t_config* term) {
    fflush(stdout);
    mx_free_assumptions(term);
    free(term->out->line);
    free(term->out->tail);
    free(term->quo);
    free(term->str);
    term->str = NULL;
    term->out->tail = NULL;
    term->out->line = NULL;
    term->quo = NULL;
    term->quo = (int *)malloc(sizeof(int) * 2);
    term->quo[0] = 0;
    term->quo[1] = 0;
    term->q_id = 0;
    term->out->len = 0;
    term->pos = 0;
    term->total = 0;
    term->entry = 0;
}

static void write_hist(int len, char *str, char *file) {
    char *tmp = mx_strndup(str, len);
    FILE * fp;

    fp = fopen (file, "a");
    fprintf(fp, "%s\t", tmp);
    fclose(fp);
    free(tmp);
}

static void reset(t_config* term, t_hist **hist) {
    write_hist(term->str_len, term->str, term->file_hist);
    term->reset = 0;
    write(1, "\n\r\x1b[0J", 6);
    mx_cooked_mode_on();
    tcsetattr(0, TCSAFLUSH, &term->origin);
    signal(SIGINT, mx_sighandler);
    signal(SIGQUIT, mx_sighandler);
    if (!strncmp("clear", term->str, 5))
        mx_clear(term->str);
    else if (!strncmp("history", term->str, 7))
        mx_history(term->str);
    else if (!strncmp("help", term->str, 4))
        mx_help(term->str);
    else
        mx_loop(term->str, term, (t_st *)term->st);
    if (hist[0]->line != NULL) {
        for (int i = 0; i < term->entry; i++) {
            free(hist[i]->line);
            hist[i]->line = NULL;
            hist[i]->len = 0;
        }
    }
    clean_up(term);
    mx_raw_mode_on();
    mx_get_cursor(&term->y, &term->x);
    term->mo_x = term->x;
    mx_refresh_line(term, 5);
}

static void inner_loop(t_config* term, t_hist **hist) {
    mx_get_term_params(term);
    write(1, "\x1b[?25h", 6);
    mx_process_key(term, hist);
    write(1, "\x1b[?25l", 6);
    mx_get_cursor(&term->y, &term->x);
    term->mo_x = term->x;
    if (!term->quo[0])
        mx_refresh_screen(term, 5);
    else if (term->quo[0] == 39 && term->quo[1] != 96)
        mx_refresh_screen(term, 7);
    else
        mx_refresh_screen(term, 8);
    if (term->reset)
        reset(term, hist);
}

void mx_lp(t_config* term, t_hist **hist) {
    mx_get_commands(term);
    mx_get_term_params(term);
    mx_raw_mode_on();
    mx_get_cursor(&term->y, &term->x);
    term->mo_x = term->x;
    term->mo_y = term->y;
    mx_refresh_line(term, 5);
    while (1)
        inner_loop(term, hist);
    mx_cooked_mode_on();
    tcsetattr(0, TCSAFLUSH, &term->origin);
}
