# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 23:30:21 by zouddach          #+#    #+#              #
#    Updated: 2024/04/17 10:48:46 by zouddach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = SRC/
OBJ_DIR = OBJ/
HEADER = $(addprefix $(SRC_DIR), pipex.h)
FILES = pipex.c utils.c childs.c ft_split.c utils2.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_DIR) 2> /dev/null || true

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: $(OBJ_DIR) clean fclean all re