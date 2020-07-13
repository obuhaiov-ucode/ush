#ifndef USH_H
#define USH_H

#include "./libmx/inc/libmx.h"

// #include "libmx.h"
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "limits.h"
#include <sys/wait.h>
#include <termcap.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <signal.h>
#include <ctype.h>
#include <stdbool.h>


#define CTRL_KEY(k) ((k) & 0x1f)
#define ABUF_INIT {NULL, 0}
#define MAXBUFSIZE (10000U)
#define MX_BACKSPACE 127
#define MX_DELBUF "\b \b"
#define MX_ARROW_LEFT 1000
#define MX_ARROW_RIGHT 1001
#define MX_ARROW_UP 1002
#define MX_ARROW_DOWN 1003
#define MX_PAGE_UP 1004
#define MX_PAGE_DOWN 1005
#define MX_HOME_KEY 1006
#define MX_END_KEY 1007
#define MX_DEL_KEY 1008

//----------sonia
#define MAXARGS 128
#define MAXLINE 1024
// maxargs used in struct, can't be variable so we have to use define
//-------------------------for future work
//typedef struct s_proc {
//    char **name;
//    pid_t pid;
//    int index;
//} t_proc;
//
//typedef struct s_prog_info {
//    struct termios old_term;
//    struct termios new_term;
//    char **env;
//    char ** history; //t_leist;
//    char **proc;
//    int exit_stat;
//    char *pwd; // ets
//    char *path;
//    char *home;
//    int last_stat;
//} t_info;
//----------------------------for future work



typedef struct s_echo {
    bool flag_n;
    bool flag_E;
    bool flag_e;
    int start_of_file;
} t_echo;


//typedef struct s_which {
//    bool flag_a;
//    int cur_arg;
//
//};


typedef struct s_app { //struct for pwd and cd
    bool flag_p; //pwd
    char *pwd_p;
    char *old_pwd_p;
    char * old_pwd_l;
    char *pwd_ll;
    char *pwd_l;
    int dot_dir;
    int cur_arg;
    char * home;
    bool dd_slesh;
    bool in_pwd;
//    char *swp;

} t_app;


typedef struct s_comand {
    int argc;
    char **argv;
    enum builtin_t {b_none, b_cd, b_echo, b_pwd, b_env,
        b_export, b_unset, b_exit, b_jobs, b_bg, b_fg, b_which} builtin;
} t_cmd;

typedef struct s_info {
    char **commands; // simple commands
    char *cmd; // input
    int *pipes;
    int pipe;

    char **fbuf;
    char **buf;

    char ***input;
    char ***output;
    char ***endout;
    int *in;
    int *out;
    int *end;

    int fd0[2];
    int fd1[2];
    int sub1[2];
    int status;
    int stat_sub;

    char *pwd_l;
    char *pwd_p;
    char *pwd_home;
    char *path;

    char *pwd;
    char *pwd_old;
    char *home;


    char **env;
    char **set;
    char **alias;

}              t_st;

typedef struct s_history {
    int id;
    int len;
    char *line;
}              t_hist;

typedef struct s_row {
    int len;
    char *tail;
    char *line;
}              t_row;

typedef struct s_config {
    struct termios origin;
    struct termios raw;
    struct s_row *out;
    int entry;
    int total;
    int *quo;
    int q_id;
    int pos;
    int x_offset;
    int row;
    int col;
    int x;
    int y;
    int reset;
    int mo_x;
    int mo_y;
    int count;
    int press;
    int num;
    int max_len;
    int str_len;
    int n;
    char **command;
    char **buf;
    char *str;
}               t_config;





int main(int argc, char **argv, char **envp);
void mx_get_commands(t_config *term);
t_config *mx_config_init(void);
t_hist **mx_hist_init(void);
void mx_write_hist(int len, char *str);
void mx_get_term_params(t_config *term);
void mx_lp(t_config *term, t_hist **hist);
void mx_raw_mode_on(void);
void mx_get_cursor(int *y, int *x);
void mx_refresh_line(t_config* term, int offset);
void mx_refresh_screen(t_config* term, int offset);
void mx_cooked_mode_on(void);
void mx_process_key(t_config *term, t_hist **hist);
void mx_qoutes_handling(t_config *term);
void mx_editor_processing(t_config* term, int c);
int mx_read_key(void);
void mx_arrows_motion(int k, t_config* term, t_hist **hist);
void mx_die(const char *str);
void mx_return_action(t_config *term, t_hist **hist);
void mx_tab_action(t_config *term);
void mx_backspace_action(t_config *term);
void mx_clear_screen(t_config* term);
void mx_free_assumptions(t_config *term);
void mx_set_cursor(t_config *term);
int mx_cd_builtin(char *argv[], t_app *app);
int mx_echo_builtin(char *argv[]);
int mx_pwd_builtin(char *argv[], t_app *pwd);
int mx_cd_p(char *argv[], t_app *pwd, int *flag);
int mx_cd_l(char *argv[], t_app *app, int *flag);
void mx_init (t_app *pwd);
bool mx_is_link(char *file);
int mx_arr_len(char **arr);
int mx_is_dot(char *argv, t_app *app);
int mx_swap_pwd (char *ch, char *argv[], t_app *app);
//int mx_which(char *argv[]);
//bool mx_is_buildin(char *str);

int mx_which(char **argv);
char *mx_join(char *s1, char *s2);
bool mx_is_buildin(char *str);
//-------------sonia






void mx_init_struct(t_st *st, char **env);
char *mx_replace_cmd(t_st *st, char *cmd);
void mx_malloc_err();
char **mx_split_line(char *line, int bufsize, int j, int k);
char **mx_split_backup(char **tokens, int bufsize, int k);
void mx_loop(char *cmd, t_config* term, t_st *st);
int mx_simple_commands(t_st *st, char **commands, t_config* term);
int mx_command_pars(t_st *st, char *c, int k, t_config* term);
int mx_check_slash(char *line, int end);
char *mx_check_env(char **arr, char *macros);
char *mx_get_env(char *c, int k);
int mx_complex_cmd(t_st *st, char **commands, int i, int passed_cmd);
char *mx_cmd_return_alias(t_st *st, char *cmd, char *tmp, char *res);
void mx_check_quotes(t_st *st);
char *mx_tilda_prefix(int start, char *cmd);
int mx_final_exe(t_st *st, char **args);
int mx_count_pipes(t_st *st, char **tokens);
int mx_conveer(t_st *st, char **tokens, t_config* term);
char **mx_get_cmd_tok(t_st *st, char **tokens, int start, int end);
void mx_piped_child(t_st *st, char **tokens, t_config* term);
int mx_streams(t_st *st, char **tokens, t_app *app);
char **mx_streams_endout(t_st *st, char **tokens, int pipe, int i);
char *mx_file_input(t_st *st, int pipe);
void mx_file_output(t_st *st, int pipe);
int mx_count_streams(char **tokens, char c, int n, int dubl);
int mx_count_term(char **tokens, char c);
char **mx_streams_in(t_st *st, char **tokens, int pipe, int i);
char **mx_streams_out(t_st *st, char **tokens, int pipe, int i);
char **mx_streams_term(t_st *st, char **tokens, int pipe, int i);
char ***mx_streams_get(t_st *st, char **tokens);
int mx_counter(char cmd, char need, int count);
int mx_ncounter(char cmd, char *need, int count, int n);
int mx_combcounter(char cmd1, char cmd2, char *need, int count);
char *mx_command_sub(t_st *st, char *cmd, char *begin, t_config *term);
int *mx_sort_intarr(int *arr);
char *mx_get_com_sub(t_config *term, char *begin, char *midl, char *final);
int mx_xcounter(char cmd, char *not_need, int n);
char *mx_get_argv(char *file, char *res);
int mx_xcombcounter(char cmd1, char cmd2, char *first_need, int count);
void mx_del_conveer(t_st *st);
int mx_get_start_sub(char *cmd);
void mx_del_chararr(char *arr);
int mx_which(char **argv);

#endif
