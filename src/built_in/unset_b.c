/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:35:54 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/14 09:04:28 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_builtin(t_cmd *cmd, t_env **env)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*save;

	curr = *env;
	save = *env;
	while (curr)
	{
		if (stcmp(cmd->cmd[1], curr->name) == 0)
		{
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
