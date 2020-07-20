#include "ush.h"

void mx_clear(char *str) {
    if (!strcmp("clear", str)) {
        mx_raw_mode_on();
        write(1, "\r", 1);
        write(1, "\x1b[2J", 4); 
        write(1, "\x1b[1;1H", 6);
    }
    else
        write(1, "\rush: clear: too many arguments\r\n", 33);
}
