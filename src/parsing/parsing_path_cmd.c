/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:41:45 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/16 11:19:55 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_path_env_splited(t_env *env, t_cmd *cmd)
{
	t_env	*curr;
	char	**paths;

	curr = env;
	while (curr && stcmp(curr->name, "PATH"))
		curr = curr->next;
	if (!curr)
		ft_perror_exit(cmd->cmd[0], 2);
	if (stcmp(curr->name, "PATH") == 0)
		paths = ft_split(curr->value, ':');
	if (!paths)
	{
		write(2, "Malloc error in get_path_env_splited\n", 37);
		return (NULL);
	}
	return (paths);
}

char	*parsing_path(t_cmd *cmd, t_env *env)
{
	char	**paths;
	char	*command;
	int		i;

	i = -1;
	paths = get_path_env_splited(env, cmd);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		command = ft_strjoin(paths[i], cmd->cmd[0]);
		free(paths[i]);
		if (access(command, F_OK) == 0)
		{
			while (paths[++i])
				free(paths[i]);
			return (command);
		}
		free(command);
	}
	return (NULL);
}
