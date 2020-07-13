NAME = ush

LIB = ./libmx/libmx.a

INC = ./inc/ush.h

HEAD = ush.h

SRCOUT = main.c \
		builtin_echo.c \
		builtin_pwd.c \
		builtin_cd.c \
		builtin_init_stract.c \
		builtin_which.c \
		mx_is_buildin.c \
		mx_join.c \
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
	mx_hist_init.c \
        mx_clear_screen.c \
		mx_cd_l.c \
		mx_cd_p.c \
		mx_is_link.c \
		mx_swap_pwd.c \
		mx_is_dot.c \
		mx_arr_length.c \
        mx_free_assumptions.c \
        mx_set_cursor.c \
        mx_write_hist.c \

SRCS = $(addprefix ./src/, $(SRCOUT))

OBJOUT = $(SRCOUT:%.c=%.o)

CFLAG = -std=c11 -Wall -Wextra -Wpedantic -Werror

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
