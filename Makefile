# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 19:44:23 by oboutarf          #+#    #+#              #
#    Updated: 2023/01/10 22:47:55 by oboutarf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell

CC 				= gcc -g3 -Wall -Wextra -Werror

OBJ				= $(SRCS:.c=.o)

SRCS 			= main/main.c \
				  srcs/free/free.c \
				  srcs/libft/libft.c \
				  srcs/parsing/parser.c \
				  srcs/signals/signals.c \
				  srcs/inits/init_tokens.c \
				  srcs/inits/init_mshell.c \
				  srcs/builtins/builtins.c \
				  srcs/inits/center_inits.c \
				  srcs/parsing/treat_quotes.c \
				  srcs/expand/center_expand.c 

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

