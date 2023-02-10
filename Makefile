

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 19:44:23 by oboutarf          #+#    #+#              #
#    Updated: 2023/02/05 06:47:15 by oboutarf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell

CC 				= gcc -g3 -Wall -Wextra -Werror -MMD # -fsanitize=address

OBJ				= $(SRCS:.c=.o)

DEP				= $(SRCS:.c=.d)

SRCS 			= main/main.c \
				  srcs/libft/libft_1.c \
				  srcs/libft/libft_2.c \
				  srcs/libft/libft_3.c \
				  srcs/libft/libft_4.c \
				  srcs/libft/libft_5.c \
				  srcs/libft/libft_6.c \
				  srcs/signals/signals.c \
				  srcs/signals/child_signals.c \
				  srcs/signals/heredoc_signals.c \
				  srcs/compose/compose_tkn.c \
				  srcs/exec/exec_exit/exit_status.c \
				  srcs/exec/exec_build/command_chain.c \
				  srcs/exec/exec_build/build_commands.c \
				  srcs/exec/exec_redirs/connect_redirs.c \
				  srcs/exec/exec_redirs/apply_redirs.c \
				  srcs/exec/exec_builtin/builtin_std.c \
				  srcs/exec/exec_builtin/exec_builtin.c \
				  srcs/exec/exec_center/arg_seeker.c \
				  srcs/exec/exec_center/exec_tools.c \
				  srcs/exec/exec_center/center_exec.c \
				  srcs/exec/exec_center/find_access.c \
				  srcs/exec/exec_center/pipe_handler.c \
				  srcs/exec/exec_center/exec_control.c \
				  srcs/exec/exec_hrdoc/execute_hrdoc.c \
				  srcs/exec/exec_hrdoc/heredoc_utils.c \
				  srcs/exec/exec_hrdoc/expand_heredoc/treat_hrdoc_delim.c \
				  srcs/exec/exec_hrdoc/expand_heredoc/expand_heredoc_utils_0.c \
				  srcs/exec/exec_hrdoc/expand_heredoc/expand_heredoc_utils_1.c \
				  srcs/exec/exec_hrdoc/expand_heredoc/expand_heredoc_utils_2.c \
				  srcs/exec/exec_hrdoc/expand_heredoc/expand_heredoc_utils_3.c \
				  srcs/token/tokenizer.c \
				  srcs/token/word_review.c \
				  srcs/token/pipe_review.c \
				  srcs/token/hrdoc_review.c \
				  srcs/token/redirs_review.c \
				  srcs/token/center_review.c \
				  srcs/free/free.c \
				  srcs/free/free_env.c \
				  srcs/free/free_built.c \
				  srcs/free/free_token.c \
				  srcs/free/free_execve.c \
				  srcs/free/free_export.c \
				  srcs/error/syntax_error.c \
				  srcs/error/error_manager.c \
				  srcs/expand/expd_tools/remove_quotes.c \
				  srcs/expand/expand_len/expand_len_types.c \
				  srcs/expand/expand_cut/expand_cut_types.c \
				  srcs/expand/expand_utils/expand_utils_0.c \
				  srcs/expand/expand_utils/expand_utils_1.c \
				  srcs/expand/expand_utils/expand_utils_2.c \
				  srcs/expand/expand_join/expand_join_types.c \
				  srcs/expand/expand_center/center_expand.c \
				  srcs/expand/expand_manage/expand_cut.c \
				  srcs/expand/expand_manage/expand_checker.c \
				  srcs/expand/expand_manage/expand_updater.c \
				  srcs/expand/expand_manage/expand_expansion.c \
				  srcs/expand/expand_manage/expand_manage_types.c \
				  srcs/inits/init_env.c \
				  srcs/inits/init_exec.c \
				  srcs/inits/init_built.c \
				  srcs/inits/init_token.c \
				  srcs/inits/init_execve.c \
				  srcs/inits/init_export.c \
				  srcs/inits/init_mshell.c \
				  srcs/inits/init_heredoc.c \
				  srcs/inits/init_expansion.c \
				  srcs/inits/no_env/no_env_init.c \
				  srcs/inits/no_env/no_env_utils.c \
				  srcs/parsing/parser.c \
				  srcs/parsing/parse_paths.c \
				  srcs/parsing/treat_pipe.c \
				  srcs/parsing/treat_redir.c \
				  srcs/parsing/treat_space.c \
				  srcs/parsing/treat_quote.c \
				  srcs/parsing/treat_export.c \
				  srcs/parsing/quote_remover.c \
				  srcs/parsing/treat_printable.c \
				  srcs/builtins/do_cd.c \
				  srcs/builtins/do_env.c \
				  srcs/builtins/do_pwd.c \
				  srcs/builtins/do_echo.c \
				  srcs/builtins/do_exit.c \
				  srcs/builtins/do_unset.c \
				  srcs/builtins/do_exprt.c \
				  srcs/builtins/export_manager.c \
				  srcs/builtins/center_builtins.c \
				  srcs/builtins/export/manage_env.c \
				  srcs/builtins/built_utils/cd_utils.c \
				  srcs/builtins/built_utils/env_utils.c \
				  srcs/builtins/built_utils/exit_utils.c \
				  srcs/builtins/built_utils/echo_utils.c \
				  srcs/builtins/built_utils/export_utils.c \

SRCH_INCLDS 	= -Iincld

RM				= rm -rf

all:        $(NAME)

%.o: %.c
			$(CC) $(SRCH_INCLDS) -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -lreadline -o $(NAME)

clean:
			$(RM) $(OBJ)
			$(RM) $(DEP)

fclean:     clean
			$(RM) $(NAME)

re:         fclean $(NAME)
