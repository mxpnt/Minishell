/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:51:42 by mapontil          #+#    #+#             */
/*   Updated: 2022/01/21 12:15:36 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_path(t_cmd *cmd, t_env *env)
{
	t_env	*curr;
	char	**paths;
	char	*command;
	int		i;

	i = -1;
	curr = env;
	while (curr && stcmp(curr->name, "PATH"))
		curr = curr->next;
	if (stcmp(curr->name, "PATH") == 0)
		paths = ft_split(curr->value, ':');
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		command = ft_strjoin(paths[i], cmd->cmd[0]);
		if (access(command, F_OK) == 0)
			if (execve(command, cmd->cmd, cmd->envp) == -1)
				return (perror("EXECVE "));
		free(command);
		free(paths[i]);
	}
}

// data->fd1 = open(..., O_RDONLY);
void	ft_fcmd(t_cmd *cmd, t_env *env, t_data *data)
{
	// if (data->fd1 < 0)
	// 	return (perror("OPEN "));
	if (dup2(data->fd1, STDIN_FILENO) < 0)
		return (perror("DUP2 "));
	if (dup2(data->end[1], STDOUT_FILENO) < 0)
		return (perror("DUP2 "));
	close(data->fd1);
	close(data->end[1]);
	close(data->end[0]);
	parsing_path(cmd, env);
}

void	ft_icmd(t_cmd *cmd, t_env *env, t_data *data)
{
	if (dup2(data->end[0], STDIN_FILENO) < 0)
		return (perror("DUP2 "));
	if (dup2(data->end[1], STDOUT_FILENO) < 0)
		return (perror("DUP2 "));
	close(data->end[0]);
	close(data->end[1]);
	parsing_path(cmd, env);
}

// Rajouter condition open pour redirection
// data->fd2 = open(..., O_CREAT | O_RDWR | O_TRUNC/O_APPEND, 0644);
void	ft_lcmd(t_cmd *cmd, t_env *env, t_data *data)
{
	if (data->fd2 < 0)
		return (perror("OPEN "));
	if (dup2(data->fd2, STDOUT_FILENO) < 0)
		return (perror("DUP2 "));
	if (dup2(data->end[0], STDIN_FILENO) < 0)
		return (perror("DUP2 "));
	close(data->fd2);
	close(data->end[0]);
	close(data->end[1]);
	parsing_path(cmd, env);
}

void	ft_exec(t_cmd *cmd, t_env *env, t_data *data, int i)
{
	if (i != 0)
	{
		if (dup2(data->prev_end, data->end[0]))
			return (perror("DUP2 "));
		close(data->prev_end);
	}
	if (i == 0)
		ft_fcmd(cmd, env, data);
	else if (!cmd->next)
		ft_lcmd(cmd, env, data);
	else
		ft_icmd(cmd, env, data);
}

// data -> mettre end[2] + fd1 & fd2 + prev_end
void	pipex(t_cmd *cmd, t_env *env, t_data *data)
{
	int	end[2];
	int	pid1;
	int	i;

	i = -1;
	while (++i < data->nb_cmd)
	{
		pipe(end);
		pid1 = fork();
		if (pid1 < 0)
			return (perror("FORK "));
		if (pid1 == 0)
			ft_exec(cmd, env, data, i);
		if (cmd->next)
		{
			data->prev_end = end[0];
			cmd = cmd->next;
		}
		close(end[0]);
		close(end[1]);
	}
	waitpid(pid1, 0, 0);
}
