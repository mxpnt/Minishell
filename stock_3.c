/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:02:49 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/26 14:50:03 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	in_x2_open(int n)
{
	int	fd;

	fd = 0;
	if (!n)
		fd = open("temp_infile", O_CREAT | O_RDWR, 0644);
	return (fd);
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

int	check_if_only_space(char *s)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (s[x] != ' ')
			return (1);
		x++;
	}
	return (0);
}
