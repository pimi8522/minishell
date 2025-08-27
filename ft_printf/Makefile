# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/24 11:09:28 by miduarte          #+#    #+#              #
#    Updated: 2025/05/06 15:58:42 by miduarte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a

CC := cc

CFLAGS := -Wall -Werror -Wextra

SRC := ft_printf.c ft_putchar.c ft_putstring.c ft_putnbr_base.c \
		ft_putnbr_unsigned.c ft_putpointer.c ft_putnbr_basex.c

OBJ := $(SRC:.c=.o)

RM := rm -f

AR := ar -rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I.

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all