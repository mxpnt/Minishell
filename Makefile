# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 10:06:54 by lsuau             #+#    #+#              #
#    Updated: 2022/02/04 13:46:31 by mapontil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEX = minishell

INC = minishell.h minishell_struct.h minishellbis.h

SRC =	main.c \
		stock_1.c \
		stock_2.c \
		stock_3.c \
		env.c \
		parsing.c \
		parsing_error.c \
		parsing_error_2.c \
		pipe_split.c \
		env_in_line.c \
		env_in_line_2.c \
		red_parsing.c \
		red_tab.c \
		red_process.c \
		cmd_lst.c \
		command.c \
		ft_split.c \
		pipex.c \
		cmd_split.c \
		handle_redirect.c \
		parsing_path_cmd.c \
		perror_exit.c

GCC = gcc #-Wall -Werror -Wextra

OBJ_DIR = obj/
OBJ = ${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}

all : ${NAMEX}

${OBJ_DIR}%.o : %.c ${INC} Makefile
	${GCC} -c $< -o $@

${NAMEX}: ${OBJ} ${INC}
	${GCC} ${OBJ} -o ${NAMEX} -lreadline -I  .brew/opt/readline/include/readline

${OBJ}: | ${OBJ_DIR}

${OBJ_DIR}:
	mkdir ${OBJ_DIR}

clean :
	rm -rf ${OBJ_DIR}

fclean : clean
	rm -f ${NAMEX}

re : fclean all

.PHONY: all clean fclean re
