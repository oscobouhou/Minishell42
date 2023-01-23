# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 19:44:23 by oboutarf          #+#    #+#              #
#    Updated: 2023/01/23 22:11:52 by oscobou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell

CC 				= gcc -g3 -Wall -Wextra -Werror -MMD

OBJ				= $(SRCS:.c=.o)

SRCS 			= main/main.c \
				  srcs/libft/libft.c \
				  srcs/signals/signals.c \
				  srcs/compose/compose_tkn.c \
				  srcs/exec/exec_build/build_commands.c \
				  srcs/exec/exec_hrdoc/treat_hrdoc_delim.c \
				  srcs/exec/exec_center/center_exec.c \
				  srcs/printer/print_tokens.c \
				  srcs/printer/print_exec_chains.c \
				  srcs/token/tokenizer.c \
				  srcs/token/word_review.c \
				  srcs/token/pipe_review.c \
				  srcs/token/hrdoc_review.c \
				  srcs/token/redirs_review.c \
				  srcs/token/center_review.c \
				  srcs/free/free.c \
				  srcs/free/free_env.c \
				  srcs/free/free_token.c \
				  srcs/free/free_export.c \
				  srcs/error/syntax_error.c \
				  srcs/error/error_manager.c \
				  srcs/expand/expd_tools/remove_quotes.c \
				  srcs/expand/expand_len/expand_len_types.c \
				  srcs/expand/expand_cut/expand_cut_types.c \
				  srcs/expand/expand_join/expand_join_types.c \
				  srcs/expand/expand_center/center_expand.c \
				  srcs/expand/expand_manage/expand_cut.c \
				  srcs/expand/expand_manage/expand_checker.c \
				  srcs/expand/expand_manage/expand_expansion.c \
				  srcs/expand/expand_manage/expand_manage_types.c \
				  srcs/inits/init_env.c \
				  srcs/inits/init_exec.c \
				  srcs/inits/init_token.c \
				  srcs/inits/init_execve.c \
				  srcs/inits/init_export.c \
				  srcs/inits/init_mshell.c \
				  srcs/inits/init_builtins.c \
				  srcs/inits/init_expansion.c \
				  srcs/parsing/parser.c \
				  srcs/parsing/parse_paths.c \
				  srcs/parsing/treat_pipe.c \
				  srcs/parsing/treat_redir.c \
				  srcs/parsing/treat_space.c \
				  srcs/parsing/treat_quote.c \
				  srcs/parsing/treat_export.c \
				  srcs/parsing/treat_printable.c \
				  srcs/builtins/do_cd.c \
				  srcs/builtins/do_env.c \
				  srcs/builtins/do_pwd.c \
				  srcs/builtins/do_echo.c \
				  srcs/builtins/do_exit.c \
				  srcs/builtins/do_unset.c \
				  srcs/builtins/do_export.c \
				  srcs/builtins/center_builtins.c \

SRCH_INCLDS 	= -Iincld

RM				= rm -rf

all:        $(NAME)

%.o: %.c
			$(CC) $(SRCH_INCLDS) -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -lreadline -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:     clean
			$(RM) $(NAME)

re:         fclean $(NAME)

