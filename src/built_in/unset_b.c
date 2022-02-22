/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:35:54 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/22 11:31:32 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_builtin(t_cmd *cmd, t_env **env)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*save;
	int		i;

	i = 1;
	while (cmd->cmd[i])
	{
		curr = *env;
		save = *env;
		prev = NULL;
		while (curr)
		{
			if (stcmp(cmd->cmd[i], curr->name) == 0)
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
		i++;
	}
}
