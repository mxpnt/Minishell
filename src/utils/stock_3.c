/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:02:49 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/04 14:29:57 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	tablen(char **tab)
{
	int	x;

	if (!tab)
		return (-1);
	x = 0;
	while (tab[x])
	{
		x++;
	}
	return (x);
}

void	write_nl(int fd, char *s)
{
	write(fd, s, stlen(s));
	write(fd, "\n", 1);
}

void	red_remove_quote(char *s)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (s[x])
	{
		if (s[x] == '\'' || s[x] == '"')
		{
			y = skip_quote(s, x);
			ft_strcpy(s + x, s + x + 1);
			ft_strcpy(s + y - 1, s + x + y);
			x = y - 1;
		}
		else
			x++;
	}
}

int	longest_in_tab(char **tab)
{
	int	x;
	int	n;
	int	len;

	n = 0;
	len = 0;
	while (tab[n])
	{
		x = 0;
		while (tab[n][x])
			x++;
		if (x > len)
			len = x;
		n++;
	}
	return (len);
}

short	satoi(char *str)
{
	short	res;
	short	neg;
	int		i;

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
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * neg);
}
