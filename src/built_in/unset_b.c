/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:35:54 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/23 17:08:33 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_excode;

static void	check_valid_unset(char *str, t_env **env)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*save;

	curr = *env;
	save = *env;
	prev = NULL;
	while (curr)
	{
		if (stcmp(str, curr->name) == 0)
		{
			if (!prev)
				save = curr->next;
			else
				prev->next = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	(*env) = save;
}

void	unset_builtin(t_cmd *cmd, t_env **env)
{
	int		i;

	i = 0;
	while (cmd->cmd[++i])
		check_valid_unset(cmd->cmd[i], env);
	g_excode = 0;
}
