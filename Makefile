# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbober <jbober@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 15:25:56 by jbober            #+#    #+#              #
#    Updated: 2024/10/14 10:48:39 by jbober           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS := -Wall -Werror -Wextra #-fsanitize=address -g
HEADERS = src/minishell.h
RM = rm -rf
INCLUDE = -lreadline

SRC_DIR = ./src
OBJ_DIR = ./obj

FILES = eidexe/cd\
		eidexe/control\
		eidexe/echo\
		eidexe/env\
		eidexe/envp\
		eidexe/exe\
		eidexe/expand\
		eidexe/export\
		eidexe/here_doc\
		eidexe/print\
		eidexe/pwd\
		eidexe/unset\
		parse/parse\
		parse/parsefk1\
		parse/parsefk1b\
		parse/parsefk2\
		parse/parsefk3\
		parse/parsefk4\
		freerror\
		minishell\
		signals\
		ut1ls\
		ut2ls\
		ut3ls\
		ut4ls\

SRC = $(addsuffix .c, $(addprefix $(SRC_DIR)/, $(FILES)))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
	