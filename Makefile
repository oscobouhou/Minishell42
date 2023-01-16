# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 19:44:23 by oboutarf          #+#    #+#              #
#    Updated: 2023/01/16 13:05:32 by oboutarf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell

CC 				= gcc -g3 -Wall -Wextra -Werror

OBJ				= $(SRCS:.c=.o)

SRCS 			= main/main.c \
				  srcs/libft/libft.c \
				  srcs/signals/signals.c \
				  srcs/error/error_manager.c \
				  srcs/compose/compose_tkn.c \
				  srcs/token/tokenizer.c \
				  srcs/token/review_tokens.c \
				  srcs/token/tokenize_heredoc.c \
				  srcs/free/free.c \
				  srcs/free/free_env.c \
				  srcs/free/free_token.c \
				  srcs/free/free_export.c \
				  srcs/expand/check_expand.c \
				  srcs/expand/export_seeker.c \
				  srcs/expand/center_expand.c \
				  srcs/expand/manage_expands.c \
				  srcs/inits/init_env.c \
				  srcs/inits/init_token.c \
				  srcs/inits/init_export.c \
				  srcs/inits/init_mshell.c \
				  srcs/inits/init_builtins.c \
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

