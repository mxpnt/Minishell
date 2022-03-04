/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 09:58:08 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 15:07:51 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || str[i] == 9)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i])
		while (str[i] == 32 || str[i] == 9)
			i++;
	if (str[i])
		return (1);
	return (0);
}

long long int	atolli(char *str)
{
	long long int	res;
	long long int	neg;
	int				i;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == 32 || str[i] == 9)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * neg);
}

int	ft_nb_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	change_value_env(char *str, t_env *env)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	while (env)
	{
		if (stcmp(env->name, name) == 0)
		{
			free(env->value);
			env->value = ft_substr(str, i + 1, stlen(str + i + 1));
			free(name);
		}
		env = env->next;
	}
}

int	check_equal(char *str)
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
