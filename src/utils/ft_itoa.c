/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:54:07 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/05 16:35:27 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static int	ft_cara_count(long long int *n, int *x)
{
	int	nbc;
	int	t;

	nbc = 0;
	if (*n == 0)
		return (1);
	if (*n < 0)
	{
		nbc++;
		*n *= -1;
		*x = 1;
	}
	t = *n;
	while (t)
	{
		nbc++;
		t /= 10;
	}
	return (nbc);
}

char	*ft_itoa(long long int n)
{
	int		nbc;
	int		x;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	x = 0;
	nbc = ft_cara_count(&n, &x);
	res = malloc(sizeof(char) * (nbc + 1));
	if (!res)
		return (0);
	if (n == 0)
		res[0] = '0';
	res[nbc] = 0;
	if (x)
		res[0] = '-';
	while (n)
	{
		res[nbc-- - 1] = (n % 10) + 48;
		n /= 10;
	}
	return (res);
}

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
