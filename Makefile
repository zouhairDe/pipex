# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 23:30:21 by zouddach          #+#    #+#              #
#    Updated: 2024/02/19 20:31:09 by zouddach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = CC
CFLAGS = -Wall -Werror -Wextra
SRC = SRC/pipex.c SRC/ft_split.c
OBJ = $(SRC:.c=.o)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: clean fclean all re