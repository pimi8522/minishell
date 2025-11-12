# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 15:37:54 by miduarte &        #+#    #+#              #
#    Updated: 2025/11/12 16:46:12 by miduarte &       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I. -Ilibft -Ipipex

SRCS = \
	srcs/main.c \
	srcs/utils.c \
	srcs/lexer/lexer_utils.c \
	srcs/lexer/lexer.c \
	srcs/signals.c \
	srcs/parser/history.c \
	srcs/parser/cmd_utils.c \
	srcs/parser/parser.c \
	srcs/parser/parser_utils.c
	

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

rec: re clean

valgrind: all clean
	valgrind --suppressions=rlbad.supp --show-leak-kinds=all --leak-check=full --track-origins=yes ./minishell

.PHONY: all clean fclean re re_clean valgrind
