/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:46:31 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/22 16:25:36 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static t_env	*env_lstnew_no_value(char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = ft_strdup(str);
	new->value = NULL;
	new->next = NULL;
	return (new);
}

static t_env	*env_lstnew_value(char const *str)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	while (str[i] != '=')
		i++;
	new->name = ft_substr(str, 0, i);
	new->value = ft_substr(str, i + 1, stlen(str + i + 1));
	new->next = NULL;
	return (new);
}

void	ft_add_env(char *str, t_data *data)
{
	t_env	*new;

	if (check_equal(str))
	{
		new = env_lstnew_value(str);
		if (!new)
		{
			env_lstclear(data);
			return ;
		}
		env_lstadd_back(&data->env, new);
	}
	else
	{
		new = env_lstnew_no_value(str);
		if (!new)
		{
			env_lstclear(data);
			return ;
		}
		env_lstadd_back(&data->env, new);
	}
}
