# CC = clang
# LIB = libmx.a
# NAME = uls

# base = check_flags compress_flags main parse proces_args uls

# get = access arrow bsize dummy grp inode links name size suffix time user

# read = full hidden standart

# sort = argv ascii_reverse ascii time_reverse time size_reverse size

# utils = errors free_dir get_data_len get_tabs inode_bsize path_name winsize

# write = 1 C CG l m name total x xG

# dirs = base get read sort utils write
# FILES = $(foreach dir, $(dirs), $($(dir):%=$(dir)/%))

# SRC_DIR = src/
# OBJ_DIR = obj/
# LIB_DIR = libmx/

# SRC = $(FILES:%=$(SRC_DIR)%.c)
# OBJ = $(FILES:%=$(OBJ_DIR)%.o)
# LIB_PATH = $(LIB_DIR)$(LIB)

# WFLAGS = -Wall -Wextra -Werror -Wpedantic
# LFLAGS = -Iinc -Ilibmx/inc
# CFLAGS = -Ofast -march=native -fomit-frame-pointer -flto
# DFLAGS = -O0 -g3 -glldb -ftrapv -fno-omit-frame-pointer -fsanitize=address

# COMPILE = $(CC) -std=c11 -pipe $(WFLAGS) $(LFLAGS)
# EXEC_IT = make -sf Makefile
# EXEC_LD = $(EXEC_IT) -C $(LIB_DIR)
# PRINT = printf
# MKDIR = mkdir -p
# RM = /bin/rm -rf
# TARGET = build

# # checking about debugging in current project
# DEBUG_OBJ = $(shell nm $(OBJ) 2> /dev/null | grep -m1 asan)
# DEBUG_BIN = $(shell nm $(NAME) 2> /dev/null | grep -m1 asan)
# DEBUG_LIB = $(shell nm $(LIB_PATH) 2> /dev/null | grep -m1 asan)


# $(OBJ_DIR):
# 	@$(MKDIR) $@ $(foreach dir, $(dirs), $@/$(dir))

# $(LIB):
# 	@$(EXEC_LD) $(TARGET)

# $(OBJ_DIR)%.o: $(SRC_DIR)%.c
# 	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $B$(<:$(SRC_DIR)%=%)$D\r"
# 	@$(COMPILE) $(CFLAGS) -o $@ -c $<

# $(NAME): $(OBJ_DIR) $(OBJ)
# 	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $R$(NAME)$D\r"
# 	@$(COMPILE) $(CFLAGS) $(LIB_PATH) $(OBJ) -o $(NAME)
# 	@$(PRINT) "$K"

# # silent mode without printing LOGO
# install: check
# 	@$(EXEC_LD) $@
# 	@$(EXEC_IT) $(NAME)

# clean:
# 	@$(EXEC_LD) $@
# 	@$(RM) $(OBJ_DIR)

# uninstall:
# 	@$(EXEC_LD) $@
# 	@$(RM) $(OBJ_DIR) $(NAME)

# # silent rebuild project
# reinstall: uninstall install

# .PHONY: all build debug check clean install uninstall reinstall

NAME = ush

LIB = ./libmx/libmx.a

INC = ./inc/ush.h

HEAD = ush.h

SRC = src

SRCOUT = main.c \
		builtin_echo.c \
		builtin_pwd.c \
		builtin_cd.c \
		builtin_init_stract.c \
		builtin_which.c \
		mx_is_builtin.c \
		mx_join_to_path.c \
        mx_init_struct.c \
        mx_replace_cmd.c \
        mx_malloc_err.c \
        mx_split_line.c \
        mx_split_backup.c \
        mx_lp.c \
        mx_command_pars.c \
        mx_simple_commands.c \
        mx_check_slash.c \
        mx_check_env.c \
        mx_get_env.c \
        mx_complex_cmd.c \
        mx_cmd_return_alias.c \
        mx_check_quotes.c \
        mx_tilda_prefix.c \
        mx_final_exe.c \
        mx_count_pipes.c \
        mx_conveer.c \
        mx_get_cmd_tok.c \
        mx_piped_child.c \
        mx_streams.c \
        mx_streams_endout.c \
        mx_file_input.c \
        mx_file_output.c \
        mx_count_streams.c \
        mx_streams_out.c \
        mx_streams_in.c \
        mx_streams_get.c \
        mx_counter.c \
        mx_ncounter.c \
        mx_combcounter.c \
        mx_command_sub.c \
        mx_get_com_sub.c \
        mx_sort_intarr.c \
        mx_xcounter.c \
        mx_get_argv.c \
        mx_xcombcounter.c \
        mx_del_conveer.c \
        mx_get_start_sub.c \
        mx_del_chararr.c \
        mx_get_commands.c \
        mx_config_init.c \
        mx_get_term_params.c \
        mx_loop.c \
        mx_raw_mode_on.c \
        mx_get_cursor.c \
        mx_refresh_line.c \
        mx_refresh_screen.c \
        mx_cooked_mode_on.c \
        mx_process_key.c \
        mx_qoutes_handling.c \
        mx_editor_processing.c \
        mx_read_key.c \
        mx_arrows_motion.c \
        mx_die.c \
        mx_return_action.c \
        mx_tab_action.c \
        mx_backspace_action.c \
        mx_clear_screen.c \
		mx_cd_l.c \
		mx_cd_p.c \
		mx_is_link.c \
		mx_swap_pwd.c \
		mx_is_dot.c \
		mx_arr_length.c \
        mx_free_assumptions.c \
        mx_set_cursor.c \
        mx_dash_spaces.c \
        mx_builtin_alias.c \
        mx_get_all_alias.c \
        mx_hist_init.c \
        mx_write_hist.c \
        builtin_env.c \
        builtin_export.c \
        builtin_unset.c \
        mx_environ_handler_env.c \
        mx_export_var_to_lists.c \
        mx_exec_env.c \
        mx_env_set_var.c \
        mx_environ_copy.c \
        mx_flags_handler_env.c \
        mx_get_var_part.c \
        mx_liststr_init.c \
        mx_liststr_push_front.c \
        mx_liststr_push_back.c \
        mx_liststr_pop_front.c \
        mx_liststr_length.c \
        mx_liststr_delete.c \
        mx_reg.c \
        mx_printerr.c \
        mx_sort_arr.c \
        mx_clear.c \
        mx_history.c \
        mx_sighandler.c \
        mx_streams_cd.c \
        mx_streams_pars.c \
        mx_without_slash.c \
        mx_any_count.c \
        mx_help.c \
        mx_control_chars.c \
        mx_shlvl_check.c \
        mx_check_cmd.c \

SRCS = $(addprefix ./src/, $(SRCOUT))

OBJOUT = $(SRCOUT:%.c=%.o)

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: install clean

install:
	@make install -C libmx
	@cp $(SRCS) .
	@cp $(INC) .
	@cp $(LIB) .
	@clang $(CFLAGS) -c $(SRCOUT) -I $(HEAD)
	@clang -ltermcap $(CFLAGS) $(LIB) $(OBJOUT) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJOUT) ./obj

clean:
	@rm -rf $(OBJOUT) $(SRCOUT) $(HEAD) obj
	@make uninstall -C libmx

uninstall: clean
	@make clean -C libmx
	@rm -rf $(NAME)
	@rm -rf libmx.a

reinstall: uninstall install
