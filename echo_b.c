/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:17:58 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/08 13:00:01 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (1);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}

static void	print_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		if (check_option(cmd->cmd[i]) == 0)
			i++;
		else
		{
			cmd->cmd[i] = clean_bs(cmd->cmd[i]);
			write(1, cmd->cmd[i], stlen(cmd->cmd[i]));
			if (cmd->cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
}

void	echo_builtin(t_cmd *cmd)
{
	int		i;
	char	*str;

	i = 0;
	while (cmd->cmd[++i])
		if ((stcmp(cmd->cmd[i], "\\") == 0 || last_char_is_bs(cmd->cmd[i]))
			&& !cmd->cmd[i + 1])
			str = readline("> ");
	print_echo(cmd);
	if (str)
	{
		write(1, str, stlen(str));
		free(str);
	}
	if (check_option(cmd->cmd[1]))
		write(1, "\n", 1);
}
