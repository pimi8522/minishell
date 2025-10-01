# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 15:37:54 by miduarte &        #+#    #+#              #
#    Updated: 2025/10/01 12:38:35 by adores & mi      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -Ipipex

SRCS = \
	srcs/main.c \
	srcs/utils.c \
	srcs/shell_split.c \
	srcs/execute.c \
	srcs/launch.c \
	srcs/signals.c \
	srcs/history.c \
	srcs/cmd_utils.c \
	srcs/parser.c \
	srcs/heredoc.c \
	srcs/expansion.c \
	builtin/builtin.c \
	builtin/builtin_utils.c\
	builtin/cd.c\
	builtin/echo.c\
	builtin/env.c\
	builtin/exit.c\
	builtin/export.c\
	builtin/pwd.c\
	builtin/unset.c\
	

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

.PHONY: all clean fclean re
