/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:18:24 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/15 16:25:58 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	nb_arg_exit(t_cmd *cmd)
{
	int	i;

	while (cmd->cmd[i])
		i++;
	if (i > 2)
		return (1);
	return (0);
}

static int	limit_arg_exit(t_cmd *cmd)
{
	long long int	nb;
	char			*temp;

	nb = atolli(cmd->cmd[1]);
	temp = ft_itoa(nb);
	if (stcmp(cmd->cmd[1], temp))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

static int	is_valid_exit(t_data *data)
{
	if (is_number(data->cmds->cmd[1]) || limit_arg_exit(data->cmds))
		return (1);
	if (nb_arg_exit(data->cmds))
		return (2);
	return (0);
}

void	exit_builtin(t_data *data)
{
	if (data->nb_cmd == 1)
	{
		write(1, "exit\n", 5);
		if (!data->cmds->cmd[1] || is_valid_exit(data) == 0)
		{
			data->run = 0;
		}
		else if (is_valid_exit(data) == 1)
		{
			// 255
			printf("minishell: exit: %s: numeric argument required\n", data->cmds->cmd[1]);
			exit(255); // remplacer par variable globale + data->run = 0 ?
		}
		else if (is_valid_exit(data) == 2)
		{
			// 1
			printf("minishell: exit: too many arguments\n");
		}
	}
}
