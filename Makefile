# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 11:31:20 by cgoldens          #+#    #+#              #
#    Updated: 2024/10/28 14:44:15 by cgoldens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I
INCLUDES	=	./
LIB		=	minilibx
SRC = so_long.c
OBJ = $(SRC:.c=.o)
NAME = so_long.a
# Règles
all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(NAME): $(OBJ)
	@make -C $(LIB)
	@cp $(LIB)/libmlx.a .
	@mv	libmlx.a $(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)
	@make clean -C $(LIB)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)/libmlx.a

re: fclean all

.PHONY: all clean fclean re
