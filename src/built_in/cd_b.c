/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:58:18 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 14:20:21 by mapontil         ###   ########.fr       */
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

static void	update_oldpwd(t_env *env, char *old)
{
	while (env)
	{
		if (stcmp(env->name, "OLDPWD") == 0)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(old);
			free(old);
		}
		env = env->next;
	}
}

static void	update_pwd(t_env *env)
{
	char	buf[PATH_MAX];
	char	*old;
	t_env	*save;

	save = env;
	while (env)
	{
		if (stcmp(env->name, "PWD") == 0)
		{
			old = ft_strdup(env->value);
			free(env->value);
			env->value = ft_strdup(getcwd(buf, PATH_MAX));
		}
		env = env->next;
	}
	env = save;
	update_oldpwd(env, old);
}

void	cd_builtin(t_cmd *cmd, t_env *env)
{
	char	*home;

	if (!cmd->cmd[1])
	{
		home = ft_strdup(home_dir(env));
		if (chdir(home) == -1)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			g_excode = 1;
		}
		else
			g_excode = 0;
		if (home)
			free(home);
		update_pwd(env);
	}
	else if (chdir(cmd->cmd[1]) == -1)
	{
		perror("cd");
		g_excode = 1;
	}
	else
		g_excode = 0;
	update_pwd(env);
}
