/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:51:42 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/23 17:18:59 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_excode;

void	last_cmd(t_cmd *cmd, t_data *data)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
		ft_perror_exit("fork", 0);
	if (pid == 0)
	{
		if (data->fd_prev)
		{
			if (dup2(data->fd_prev, STDIN_FILENO) == -1)
				ft_perror_exit("dup2", 0);
			close(data->fd_prev);
		}
		if (cmd->in)
			ft_handle_redirect_in(cmd);
		if (cmd->out)
			ft_handle_redirect_out(cmd);
		if (!cmd->cmd[0])
			exit(0);
		if (handle_builtin(cmd, data))
			exit(0);
		if (!cmd->path[0])
			ft_command_not_found(cmd->cmd[0]);
		if (execve(cmd->path, cmd->cmd, cmd->envp) == -1)
			ft_perror_exit(cmd->cmd[0], 0);
	}
	if (data->fd_prev)
		close(data->fd_prev);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			g_excode = 130;
		else if (WTERMSIG(status) == 3)
		{
			write(1,"Quit: 3", 8);
			g_excode = 131;
		}
		else
			g_excode = WTERMSIG(status);
		write(1, "\n", 1);
	}
	else if (WIFEXITED(status))
	{
		g_excode = WEXITSTATUS(status);
	}
	while (waitpid(-1, &pid, 0) != -1)
		;
}

void	ft_exec(t_cmd *cmd, t_data *data)
{
	if (data->fd_prev)
	{
		if (dup2(data->fd_prev, STDIN_FILENO) == -1)
			ft_perror_exit("dup2", 0);
		close(data->fd_prev);
	}
	if (cmd->in)
		ft_handle_redirect_in(cmd);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		ft_perror_exit("dup2", 0);
	close(data->fd[1]);
	if (handle_builtin(cmd, data))
		exit(0);
	if (!cmd->path[0])
		ft_command_not_found(cmd->cmd[0]);
	if (execve(cmd->path, cmd->cmd, cmd->envp) == -1)
		ft_perror_exit(cmd->cmd[0], 0);
}

void	pipex(t_cmd *cmd, t_env *env, t_data *data)
{
	int	pid;

	signal_child_handler(data);
	data->fd_prev = 0;
	if (is_builtin(cmd->cmd[0]) && data->nb_cmd == 1)
		which_builtin(data->cmds, data, is_builtin(cmd->cmd[0]));
	else
	{
		while (cmd->next)
		{
			pipe(data->fd);
			pid = fork();
			if (pid < 0)
				ft_perror_exit("fork", 0);
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
}