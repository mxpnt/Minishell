# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 10:06:54 by lsuau             #+#    #+#              #
#    Updated: 2022/01/14 19:22:51 by lsuau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEX = minishell

INC = minishell.h minishell_lst.h

SRC = main.c stock_1.c env.c parsing.c parsing_error.c pipe_split.c

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
