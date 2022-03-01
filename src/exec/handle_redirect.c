/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:40:41 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/01 15:03:01 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	ft_handle_redirect_out(t_cmd *cmd)
{
	int	fd_redi;

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

void	ft_handle_redirect_in(t_cmd *cmd)
{
	int	fd_redi;

	if (cmd->red_in == 0)
	{
		fd_redi = open(cmd->in, O_RDONLY);
		if (dup2(fd_redi, STDIN_FILENO) == -1)
			ft_perror_exit("dup2", 0);
		close(fd_redi);
	}
	if (cmd->red_in == 1)
	{
		unlink(cmd->in);
	}
}
