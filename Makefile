# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miduarte & adores <miduarte@student.42l    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 15:37:54 by miduarte &        #+#    #+#              #
#    Updated: 2025/11/07 18:47:21 by miduarte &       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -Ipipex

SRCS = \
	srcs/main.c \
	srcs/utils.c \
	srcs/lexer/lexer_utils.c \
	srcs/lexer/lexer.c \
	srcs/execute.c \
	srcs/execute_pipeline.c \
	srcs/launch.c \
	srcs/signals.c \
	srcs/parser/history.c \
	srcs/parser/cmd_utils.c \
	srcs/parser/parser.c \
	srcs/parser/parser_utils.c \
	srcs/heredoc.c \
	srcs/expansion.c \
	builtin/builtin.c \
	builtin/cd.c\
	builtin/echo.c\
	builtin/env.c\
	builtin/env_convert.c\
	builtin/env_create.c\
	builtin/env_utils.c\
	builtin/exit.c\
	builtin/export.c\
	builtin/pwd.c\
	builtin/unset.c\
	builtin/cd_utils.c
	

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
