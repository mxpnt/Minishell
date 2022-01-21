/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:55:30 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/21 11:50:46 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;
//in and out -> file name, null if not specified
//red_in and red_out -> redirection type, 0 by default, 1 if double
//red_in == -1 if file do not exist
//if red_in == 1, in file must be deleted
typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	char			*in;
	int				red_in;
	char			*out;
	int				red_out;
	char			**envp;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_env	*env;
	t_cmd	*cmds;
	int		nb_cmd;
	int		end[2];
	int		fd1;
	int		fd2;
	int		prev_end;
	int		error;
	int		run;
}	t_data;

#endif