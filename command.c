/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:45:27 by mapontil          #+#    #+#             */
/*   Updated: 2022/01/17 16:16:10 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *env)
{
	while (env)
	{
		if (stcmp(env->name, "PWD"))
		{
			write(1, env->value, stlen(env->value));
			return ;
		}
		env = env->next;
	}
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	fd;

	if (cmd->out && cmd->red_out == 0)
		fd = open(cmd->out, O_RDWR | O_CREAT);
	else if (cmd->out && cmd->red_out == 1)
		fd = open(cmd->out, O_RDWR | O_APPEND);
	i = 1;
	while (cmd->cmd[i])
	{
		if (!cmd->out)
			write(1, cmd->cmd[i], stlen(cmd->cmd[i]));
		else
			write(fd, cmd->cmd[i], stlen(cmd->cmd[i]));
		i++;
	}
	if (cmd->out)
		close(fd);
}

void	ft_env(t_env *env)
{
	char	*str;

	while (env)
	{
		str = ft_strjoin(env->name, "=");
		str = ft_strjoin(str, env->value);
		write(1, str, stlen(str));
		write(1, "\n", 1);
		env = env->next;
	}
}

void	ft_unset(t_env *env, t_cmd *cmd)
{
	t_env	*save;
	int		i;

	i = 1;
	while (env)
	{
		if (stcmp(cmd->cmd[i], env->name))
		{
			if (save)
				save->next = env->next;
			free(env->name);
			free(env->value);
			free(env);
			return ;
		}
		save = env;
		env = env->next;
	}
}

void	ft_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
		i++;
	if (i != 1)
		return ;
}
