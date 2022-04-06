/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:40:41 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/28 11:30:40 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static void	ft_handle_redirect_in2(t_cmd *cmd)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(cmd->in, 2);
	write(2, ": ambigous redirect\n", 20);
	exit(1);
}

void	ft_handle_redirect_out(t_cmd *cmd)
{
	int	fd_redi;

	if (cmd->red_out == -1)
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(cmd->out, 2);
		write(2, ": Permission denied\n", 20);
		exit(1);
	}
	if (cmd->red_out == 0)
	{
		fd_redi = open(cmd->out, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (dup2(fd_redi, STDOUT_FILENO) == -1)
			ft_perror_exit("dup2", 0);
		close(fd_redi);
	}
	else if (cmd->red_out == 1)
	{
		fd_redi = open(cmd->out, O_RDWR | O_APPEND, 0644);
		if (dup2(fd_redi, STDOUT_FILENO) == -1)
			ft_perror_exit("dup2", 0);
		close(fd_redi);
	}
}

static void	error_redirect_in(t_cmd *cmd)
{
	if (access(cmd->in, F_OK))
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(cmd->in, 2);
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(cmd->in, 2);
		write(2, ": Permission denied\n", 20);
	}
	exit(1);
}

void	ft_handle_redirect_in(t_cmd *cmd)
{
	int	fd_redi;

	if (cmd->red_in == -1)
		error_redirect_in(cmd);
	else if (cmd->red_in == -2)
		ft_handle_redirect_in2(cmd);
	if (cmd->red_in == 0 || cmd->red_in == 1)
	{
		fd_redi = open(cmd->in, O_RDONLY);
		if (dup2(fd_redi, STDIN_FILENO) == -1)
			ft_perror_exit("dup2", 0);
		close(fd_redi);
	}
}
