# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 11:31:20 by cgoldens          #+#    #+#              #
#    Updated: 2024/10/15 14:52:34 by cgoldens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I
INCLUDES	=	include/
LIBFT		=	libft
SRC = src/ft_printf.c src/ft_printf_utils1.c src/ft_printf_utils2.c
OBJ = $(SRC:.c=.o)
NAME = libftprintf.a
# Règles
all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@cp libft/libft.a .
	@mv	libft.a $(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re
