/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:03:19 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/02 16:50:02 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

void	pwd_builtin(t_env *env)
{
	while (env)
	{
		if (stcmp(env->name, "PWD") == 0)
		{
			write(1, env->value, stlen(env->value));
			write(1, "\n", 1);
			break ;
		}
		env = env->next;
	}
	g_excode = 0;
}
