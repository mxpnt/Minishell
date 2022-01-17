/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:32:35 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/17 16:10:56 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell_lst.h"

typedef struct s_data
{
	t_env	*env;
	t_cmd	*cmds;
	int		error;
	int		run;
}	t_data;

t_env	*env_init(t_data *data, char **envp);
void	env_lstclear(t_data *data);
int		mess_error(t_data *data, int n);

int		le_parsing(t_data *data, char *line);
int		check_quote_n_pipe(char *line);
int		check_red(char *line);
int		wrong_redcara(char *line);
char	**pipe_split(char *line);
int		char_count(char	*line, char c);

int		stcmp(const char *s1, const char *s2);
int		stlen(const char *s);
char	*ft_substr(char const	*s, int start, int len);
char	*ft_strdup(const char *s1);
char	**free_tab(char	**tab);

// command.c
void	ft_pwd(t_env *env);
void	ft_echo(t_cmd *cmd);
void	ft_env(t_env *env);
void	ft_unset(t_env *env, t_cmd *cmd);

// stock_2.c
char	*ft_strjoin(char *s1, char *s2);

#endif