# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 19:44:23 by oboutarf          #+#    #+#              #
#    Updated: 2023/01/20 12:38:42 by oboutarf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell

CC 				= gcc -g3 -Wall -Wextra -Werror

OBJ				= $(SRCS:.c=.o)

SRCS 			= main/main.c \
				  srcs/libft/libft.c \
				  srcs/signals/signals.c \
				  srcs/printer/print_tokens.c \
				  srcs/compose/compose_tkn.c \
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
				  srcs/expand/make_expand.c \
				  srcs/expand/center_expand.c \
				  srcs/expand/suppress_expand.c \
				  srcs/expand/expand_in_hrdoc.c \
				  srcs/expand/check_valid_expand.c \
				  srcs/expand/search_expand_in_expt.c \
				  srcs/inits/init_env.c \
				  srcs/inits/init_token.c \
				  srcs/inits/init_export.c \
				  srcs/inits/init_mshell.c \
				  srcs/inits/init_builtins.c \
				  srcs/inits/init_expansion.c \
				  srcs/parsing/parser.c \
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
			$(CC) $(SRCH_INCLDS) -Iusr/local/include -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -lreadline -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:     clean
			$(RM) $(NAME)

re:         fclean $(NAME)

