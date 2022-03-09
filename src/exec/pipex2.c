/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:10:36 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/09 11:39:46 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	start_exec(t_cmd *cmd, t_data *data)
{
	if (data->fd_prev)
	{
		if (dup2(data->fd_prev, STDIN_FILENO) == -1)
			ft_perror_exit("dup2", 0);
		close(data->fd_prev);
	}
	if (!cmd->path[0] && (cmd->in || cmd->out)
		&& cmd->red_in != -1 && cmd->red_out != -1)
		exit(0);
	else if (!cmd->path[0] && !is_builtin(cmd->cmd[0])
		&& !cmd->in && !cmd->out)
		ft_command_not_found(cmd->cmd[0]);
}
