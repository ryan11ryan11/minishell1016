# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbober <jbober@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 15:25:56 by jbober            #+#    #+#              #
#    Updated: 2024/10/16 16:51:46 by jbober           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS := -Wall -Werror -Wextra -g #-fsanitize=address
HEADERS = src/minishell.h
RM = rm -rf
INCLUDE = -lreadline

SRC_DIR = ./src
OBJ_DIR = ./obj

FILES = parse/parse\
		parse/parsefk1\
		parse/parsefk1b\
		parse/parsefk2\
		parse/parsefk3\
		parse/parsefk4\
		parse/parsefk5\
		parse/parsefk5b\
		freerror\
		minishell\
		signals\
		ut1ls\
		ut2ls\
		ut3ls\
		ut4ls\
		ut5ls\
		execution/src/utils\
		execution/src/builtin_control\
		execution/src/envlistclear\
		execution/src/envp_list_maker\
		execution/src/ft_cd\
		execution/src/ft_echo\
		execution/src/ft_env\
		execution/src/ft_export\
		execution/src/ft_export2\
		execution/src/ft_export3\
		execution/src/ft_export4\
		execution/src/ft_export5\
		execution/src/ft_pwd\
		execution/src/ft_unset\
		execution/src/heredoc_signal\
		execution/src/pipe_utils\
		execution/src/pipe_utils2\
		execution/src/pipe_utils3\
		execution/src/pipe_utils4\
		execution/src/pipe\
		execution/src/pipe2\
		execution/src/signal\
		execution/src/util\
		execution/src/ft_lib\
		execution/src/ft_lib2\
		#eidexe/control\
		#eidexe/echo\
		#eidexe/env\
		#eidexe/envp\
		#eidexe/exe\
		#eidexe/expand\
		#eidexe/export\
		#eidexe/here_doc\
		#eidexe/print\
		#eidexe/pwd\
		#eidexe/unset\


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
	