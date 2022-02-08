/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:51:42 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/08 14:59:18 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	last_cmd(t_cmd *cmd, t_data *data)
{
	char	*command_path;
	int		pid;

	pid = fork();
	if (pid < 0)
		ft_perror_exit("FORK ");
	if (pid == 0)
	{
		if (data->fd_prev)
		{
			if (dup2(data->fd_prev, STDIN_FILENO) == -1)
				ft_perror_exit("DUP2 ");
			close(data->fd_prev);
		}
		if (cmd->in)
			ft_handle_redirect_in(cmd);
		if (cmd->out)
			ft_handle_redirect_out(cmd);
		if (handle_builtin(cmd, data))
		{
			exit(0);
		}
		command_path = parsing_path(cmd, data->env);
		if (!cmd->path[0])
			ft_perror_exit("PATH ");
		if (execve(cmd->path, cmd->cmd, cmd->envp) == -1)
			ft_perror_exit("EXECVE ");
	}
	if (data->fd_prev)
		close(data->fd_prev);
	while (waitpid(-1, &pid, 0) != -1)
		; // waitpid last cmd to update "$?" and handle signal
}

void	ft_exec(t_cmd *cmd, t_data *data)
{
	char	*command_path;

	if (data->fd_prev)
	{
		if (dup2(data->fd_prev, STDIN_FILENO) == -1)
			ft_perror_exit("DUP2 ");
		close(data->fd_prev);
	}
	if (cmd->in)
		ft_handle_redirect_in(cmd);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		ft_perror_exit("DUP2 ");
	close(data->fd[1]);
	// handle_builtin(cmd, data);
	command_path = parsing_path(cmd, data->env);
	if (!cmd->path[0])
		ft_perror_exit("PATH ");
	if (execve(cmd->path, cmd->cmd, cmd->envp) == -1)
		ft_perror_exit("EXECVE ");
}

void	pipex(t_cmd *cmd, t_env *env, t_data *data)
{
	int	pid;

	data->fd_prev = 0;
	while (cmd->next)
	{
		pipe(data->fd);
		pid = fork();
		if (pid < 0)
			ft_perror_exit("FORK ");
		if (pid == 0)
		{
			close(data->fd[0]);
			ft_exec(cmd, data);
		}
		if (data->fd_prev)
			close(data->fd_prev);
		data->fd_prev = data->fd[0];
		close(data->fd[1]);
		cmd = cmd->next;
	}
	last_cmd(cmd, data);
}
