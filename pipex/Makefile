# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adores <adores@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 10:49:23 by adores            #+#    #+#              #
#    Updated: 2025/08/07 14:45:34 by adores           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LFLAGS =  -Llibft -lft 

SRC = pipex.c utils.c utils2.c

HEADER = pipex.h


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) -I.

clean:
	rm -f $(OBJ) $(LIBFT)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all


.PHONY: all clean fclean re mlx