/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:58:18 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/02 13:07:45 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

static char	*home_dir(t_env *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (stcmp(env->name, "HOME") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	cd_builtin(t_cmd *cmd, t_env *env)
{
	char	*home;

	if (!cmd->cmd[1])
	{
		home = ft_strdup(home_dir(env));
		if (chdir(home) == -1)
		{
			write(1, "minishell: cd: HOME not set\n", 28);
			g_excode = 1;
		}
		else
			g_excode = 0;
		if (home)
			free(home);
	}
	else if (chdir(cmd->cmd[1]) == -1)
	{
		perror("cd");
		g_excode = 1;
	}
	else
		g_excode = 0;
}
