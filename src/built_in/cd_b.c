/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:58:18 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/23 17:29:26 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_excode;

void	cd_builtin(t_cmd *cmd)
{
	if (chdir(cmd->cmd[1]) == -1)
	{
		perror("cd");
		g_excode = 1;
	}
	else
		g_excode = 0;
}
