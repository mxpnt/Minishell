/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:34:52 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/02 11:52:52 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell_struct.h"

// cd_b.c
void	cd_builtin(t_cmd *cmd, t_env *env);

// echo_b.c
void	echo_builtin(t_cmd *cmd);

// env_b.c
void	env_builtin(t_env *env);

// exit_b.c
void	exit_builtin(t_data *data);

// export_b.c
void	export_builtin(t_data *data, t_cmd *cmd);

// export2_b.c
void	ft_add_env(char *str, t_data *data);

// pwd_b.c
void	pwd_builtin(t_env *env);

// unset_b.c
void	unset_builtin(t_cmd *cmd, t_env **env);

#endif