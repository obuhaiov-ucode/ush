#include "ush.h"

static int end_quotes(char *cmd, char q, int n) {
    if (q == '"' || q == '`') {
        for (int i = 0; cmd[i] != '\0' && q == '"'; i++) {
            if (cmd[i] == q)
                n++;
        }
        for (int i = 0; cmd[i] != '\0' && q == '`'; i++) {
            if (cmd[i] == q)
                n++;
        }
    }
    else {
        for (int i = 0; cmd[i] != '\0'; i++) {
            if (strncmp(&cmd[i], "'", 1) == 0)
                n++;
        }
    }
    if (n % 2 != 0)
        return 1;
    return 0;
}

static int odd_quotes(char *cmd, char q, int opened, int closed) {
    if (q == '{' || q == '}' || q == '(' || q == ')') {
        for (int i = 0; cmd[i] != '\0' && (q == '{' || q == '}'); i++) {
            opened = mx_counter(cmd[i], '{', opened);
            closed = mx_counter(cmd[i], '}', closed);
            if (opened - closed < 0)
                return 1;
        }
        for (int i = 0; cmd[i] != '\0' && (q == '(' || q == ')'); i++) {
            opened = mx_counter(cmd[i], '(', opened);
            closed = mx_counter(cmd[i], ')', closed);
            if (opened - closed < 0)
                return 1;
        }
        if (opened - closed != 0)
            return 1;
    }
    else if (end_quotes(cmd, q, 0) != 0)
        return 1;
    return 0;
}

int mx_check_quotes(char *cmd) {
    for (int i = 0; cmd[i] != '\0'; i++) {
        if (strncmp(&cmd[i], "'", 1) == 0
            || cmd[i] == '"' ||  cmd[i] == '('
            || cmd[i] == ')' ||  cmd[i] == '{'
            || cmd[i] == '}' ||  cmd[i] == '`') {
            if (odd_quotes(cmd, cmd[i], 0, 0) != 0)
                return 1;
        }
    }
    return 0;
}
