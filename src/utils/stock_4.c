/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:22:56 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/16 09:05:17 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_lower_case(char *str)
{
	int		i;
	char	*dup;

	if (!str)
		return (NULL);
	i = 0;
	dup = ft_strdup(str);
	while (dup[i])
	{
		if (dup[i] >= 'A' && dup[i] <= 'Z')
			dup[i] += 32;
		i++;
	}
	return (dup);
}

int	last_char_is_bs(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	if (str[i] == '\\' && (i == 0 || str[i - 1] != '\\'))
		return (1);
	return (0);
}

char	*clean_bs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\0' || str[i] != '\\'))
			str[i] = '\0';
		i++;
	}
	return (str);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = stlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (0);
}

char	*ft_userchr(t_data *data)
{
	t_env	*curr;
	char	*name;

	curr = data->env;
	if (!curr)
		return (NULL);
	while (curr)
	{
		if (stcmp(curr->name, "USER") == 0)
			name = ft_strdup(curr->value);
		curr = curr->next;
	}
	return (name);
}
