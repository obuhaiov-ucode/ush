#include "ush.h"

void mx_set_cursor(t_config *term) {
    if (term->num > 1 && term->x + term->x_offset >= term->row)
        term->mo_x = term->row - term->x_offset;
        if (term->mo_x < 0) {
            write(1, "\r\n", 2);
            mx_refresh_line(term, 5);
            write(1, term->out->line, term->out->len);
            term->mo_y = term->out->len + 1;
        }
    write(1, "\x1b[", 2);
    write(1, mx_itoa(term->mo_x), strlen(mx_itoa(term->mo_x)));
    write(1, ";", 1);
    write(1, mx_itoa(term->mo_y), strlen(mx_itoa(term->mo_y)));
    write(1, "H", 1);
}
