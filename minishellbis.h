/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellbis.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:17:45 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/04 13:45:44 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLBIS_H
# define MINISHELLBIS_H

# include <fcntl.h>
# include <signal.h>
# include "minishell_struct.h"

// command.c
void	ft_pwd(t_env *env);
void	ft_echo(t_cmd *cmd);
void	ft_env(t_env *env);
void	ft_unset(t_env *env, t_cmd *cmd);
void	ft_exit(t_cmd *cmd, t_data *data);

// pipex.c
void	pipex(t_cmd *cmd, t_env *env, t_data *data);
void	ft_exec(t_cmd *cmd, t_data *data);
void	last_cmd(t_cmd *cmd, t_data *data);

// parsing_path_cmd.c
char	**get_path_env_splited(t_env *env);
char	*parsing_path(t_cmd *cmd, t_env *env);

// perror_exit.c
void	ft_perror_exit(const char *str);

// handle_redirect.c
void	ft_handle_redirect_out(t_cmd *cmd);
void	ft_handle_redirect_in(t_cmd *cmd);

// execute.c
void	le_exec(t_cmd *cmd, t_env *env, t_data *data);

// ex_built.c
int		is_builtin(char **str);
void	which_builtin(t_cmd *cmd, t_env *env, t_data *data, int n);

// stock_2.c
char	*ft_strjoin(char *s1, char *s2);

// stock_4.c
char	*ft_lower_case(char *str);

// ft_split.c
char	**ft_split(char const *s, char c);

// signal.c
void	signal_c(int signum);

#endif