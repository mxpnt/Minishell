/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellbis.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:17:45 by mapontil          #+#    #+#             */
/*   Updated: 2022/01/26 15:00:01 by mapontil         ###   ########.fr       */
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
void	ft_exec(t_cmd *cmd, t_env *env, t_data *data, int i);
void	ft_lcmd(t_cmd *cmd, t_env *env, t_data *data);
void	ft_icmd(t_cmd *cmd, t_env *env, t_data *data);
void	ft_fcmd(t_cmd *cmd, t_env *env, t_data *data);
void	parsing_path(t_cmd *cmd, t_env *env);

// stock_2.c
char	*ft_strjoin(char *s1, char *s2);

// ft_split.c
char	**ft_split(char const *s, char c);

// signal.c
void	signal_c(int signum);

#endif