/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lst.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:55:30 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/17 15:44:51 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LST_H
# define MINISHELL_LST_H

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
	struct s_cmd	*next;
}	t_cmd;

#endif