# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 19:44:23 by oboutarf          #+#    #+#              #
#    Updated: 2023/01/09 20:29:31 by oboutarf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell

CC 				= gcc -g3 -Wall -Wextra -Werror

OBJ				= $(SRCS:.c=.o)

SRCS 			= main/main.c \
				  srcs/init.c \
				  srcs/libft.c \
				  srcs/parser.c \
				  srcs/signals.c \
				  srcs/builtins.c \
				  srcs/free.c \

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

