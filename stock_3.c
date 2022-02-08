/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:02:49 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/04 16:47:17 by lsuau            ###   ########.fr       */
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

int	in_x2_open(t_cmd *cmd)
{
	int			fd;
	static int	x;
	char		*t;
	char		*n;

	t = ft_strdup("temp_infile_");
	n = ft_itoa(x);
	cmd->in = ft_strjoin(t, n);
	if (t)
		free(t);
	if (n)
		free(n);
	if (!cmd->in)
		return (0);
	x++;
	if (!cmd->next)
		x = 0;
	fd = open(cmd->in, O_CREAT | O_RDWR, 0644);
	cmd->red_in = 1;
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
