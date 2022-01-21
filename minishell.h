/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:32:35 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/21 13:23:59 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell_struct.h"
# include "minishellbis.h"

//env
t_env	*env_init(t_data *data, char **envp);
void	env_lstclear(t_data *data);
int		env_lstsize(t_env	*env);
int		replace_env_line(t_env *env, char **line);
void	remove_wrong_env(char *line);
//cmd format
int		le_parsing(t_data *data, char *line);
char	**pipe_split(char *line);
//-->redirection
int		red_parsing(t_data *data, t_cmd	*cmd, char *line);
char	**fill_red_tab(char *line, char c);
int		red_count(char *line, char c);
//-->cmd lst
t_cmd	*cmd_lstnew(t_data *data);
void	cmd_lstadd_back(t_cmd **alst, t_cmd *new);
int		cmd_lstclear(t_data *data);
//check error
int		mess_error(t_data *data, char c, const char *s, int n);
int		check_quote_n_pipe(t_data *data, char *line);
int		check_red(t_data *data, char *line);
int		wrong_redcara(t_data *data, char *line);
//utils
int		stcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		stlen(const char *s);
char	*ft_substr(char const	*s, int start, int len);
char	*ft_strdup(const char *s1);
char	**free_tab(char	**tab);
int		skip_quote(char *line, int x);
void	ft_strcpy(char *dst, const char *src);
//temp
void	print_tab(char **tab);
#endif