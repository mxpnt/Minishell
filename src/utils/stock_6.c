/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 08:42:47 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/08 08:43:14 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	ft_atoi(const char *str)
{
	int		x;
	long	res;
	int		fact;

	x = 0;
	res = 0;
	fact = 1;
	while (str[x] == ' ' || (str[x] >= '\t' && str[x] <= '\r'))
		x++;
	if (str[x] == '-')
	{
		x++;
		fact = -1;
	}
	else if (str[x] == '+')
		x++;
	while (str[x] >= '0' && str[x] <= '9')
	{
		res = res * 10 + str[x++] - '0';
		if (res > 2147483648 && fact == -1)
			return (0);
		else if (res > 2147483647 && fact == 1)
			return (-1);
	}
	return (res * fact);
}
