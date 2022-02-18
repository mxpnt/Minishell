# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 10:06:54 by lsuau             #+#    #+#              #
#    Updated: 2022/02/16 14:52:57 by lsuau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

INC 		=	inc/minishell.h inc/minishell_struct.h inc/minishellbis.h

SRC			=	main.c \
				prompt.c

BUILT_IN	=	echo_b.c \
				env_b.c \
				exit_b.c \
				export_b.c \
				pwd_b.c \
				unset_b.c

EXEC		=	handle_builtins.c \
				handle_redirect.c \
				perror_exit.c \
				pipex.c \
				red_parsing.c \
				red_process.c \
				red_tab.c

PARSING		=	cmd_lst.c \
				cmd_split.c \
				env_in_line.c \
				env_in_line_2.c \
				env.c \
				parsing_error.c \
				parsing_error_2.c \
				parsing_path_cmd.c \
				parsing.c \
				pipe_split.c \
				herdoc.c

SIGNAL		=	signal.c

UTILS		=	ft_itoa.c \
				ft_split.c \
				megajoin.c \
				stock_1.c \
				stock_2.c \
				stock_3.c \
				stock_4.c \
				stock_5.c

SRCS		=	${SRC} \
				${addprefix built_in/, ${BUILT_IN}} \
				${addprefix exec/, ${EXEC}} \
				${addprefix parsing/, ${PARSING}} \
				${addprefix signal/, ${SIGNAL}} \
				${addprefix utils/, ${UTILS}}

OBJS		=	${addprefix objs/, ${SRCS:.c=.o}}

CC			=	gcc
# CFLAGS		=	-Wall -Wextra -Werror

all:		${NAME}
objs/%.o:	src/%.c ${INC}
			@mkdir -p $(dir $@)
			${CC} -c $< -o $@

${NAME}:	${OBJS} ${INC}
			${CC} -lreadline -I  .brew/opt/readline/include/readline -o ${NAME} ${OBJS}

clean:
			rm -rf objs/

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
