# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 10:06:54 by lsuau             #+#    #+#              #
#    Updated: 2022/01/21 13:28:28 by lsuau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEX = minishell

INC = minishell.h minishell_struct.h minishellbis.h

SRC =	main.c \
		stock_1.c \
		stock_2.c \
		env.c \
		parsing.c \
		parsing_error.c \
		parsing_error_2.c \
		pipe_split.c \
		env_in_line.c \
		red_parsing.c \
		red_tab.c \
		cmd_lst.c \
		\
		command.c \
		ft_split.c \
		pipex.c \
		signal.c \

GCC = gcc #-Wall -Werror -Wextra

OBJ_DIR = obj/
OBJ = ${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}

all : ${NAMEX}

${OBJ_DIR}%.o : %.c ${INC} Makefile
	${GCC} -c $< -o $@

${NAMEX}: ${OBJ} ${INC}
	${GCC} ${OBJ} -o ${NAMEX} -lreadline

${OBJ}: | ${OBJ_DIR}

${OBJ_DIR}:
	mkdir ${OBJ_DIR}

clean :
	rm -rf ${OBJ_DIR}

fclean : clean
	rm -f ${NAMEX}

re : fclean all

.PHONY: all clean fclean re
