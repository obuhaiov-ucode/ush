#include "ush.h"

int mx_match_search(char *str, char *regex) {
    regex_t reg;
    int res;

    regcomp(&reg, regex, REG_EXTENDED);
    res = regexec(&reg, str, 0, NULL, 0);
    regfree(&reg);
    return res == 0;
}
