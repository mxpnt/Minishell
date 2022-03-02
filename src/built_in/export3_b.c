/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:55:19 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/02 18:43:34 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

int	valid_identifier(char *str, int mod)
{
	int	i;

	i = 0;
	if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z')
		&& str[i] != '_')
	{
		if (mod == 0)
			printf("minishell: export: `%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[i])
	{
		if (!(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& str[i] != '_' && !(str[i] >= '0' && str[i] <= '9'))
		{
			if (mod == 0)
				printf("minishell: export: `%s': not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}
