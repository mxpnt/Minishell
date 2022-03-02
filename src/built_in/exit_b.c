/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:18:24 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/02 13:14:29 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

static int	nb_arg_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
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

static void	exit_numeric(t_data *data)
{
	printf("minishell: exit: %s: numeric argument required\n", \
	data->cmds->cmd[1]);
	cmd_lstclear(data);
	env_lstclear(data);
	exit(255);
}

void	exit_builtin(t_data *data)
{
	if (data->nb_cmd == 1)
	{
		write(1, "exit\n", 5);
		if (!data->cmds->cmd[1] || is_valid_exit(data) == 0)
		{
			data->run = 0;
			if (data->cmds->cmd[1])
				g_excode = satoi(data->cmds->cmd[1]);
			else
				g_excode = 0;
			cmd_lstclear(data);
			env_lstclear(data);
			exit(g_excode);
		}
		else if (is_valid_exit(data) == 1)
			exit_numeric(data);
		else if (is_valid_exit(data) == 2)
		{
			printf("minishell: exit: too many arguments\n");
			g_excode = 1;
		}
	}
}
