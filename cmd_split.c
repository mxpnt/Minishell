/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:29:44 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/29 16:09:08 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_count(char *line)
{
	int	x;
	int	nb_token;

	x = 0;
	nb_token = 0;
	while (line[x])
	{
		if (line[x] != ' ')
			nb_token++;
		while (line[x] && line[x] != ' ')
		{
			if (line[x] == '\'' || line[x] == '"')
				x = skip_quote(line, x) + 1;
			else
				x++;
		}
		while (line[x] == ' ')
			x++;
	}
	return (nb_token);
}

int	cmd_stlen(char *line)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (line[x])
	{
		if (line[x] == '\'' || line[x] == '"')
			x = skip_quote(line, x);
		if (!line[x] || line[x] == ' ')
			return (x);
		x++;
	}
	return (x);
}

char	*cmd_substr(char *line)
{
	int		x;
	int		len;
	char	*s;

	x = 0;
	while (line[x])
	{
		if (line[x] != ' ')
		{
			len = cmd_stlen(line + x);
			s = ft_substr(line, x, len);
			ft_strcpy(line + x, line + x + len);
			return (s);
		}
		x++;
	}
	return (0);
}

char	**cmd_split(char *line)
{
	char	**tab;
	int		nb_token;
	int		n;

	nb_token = token_count(line);
	tab = malloc(sizeof(char *) * (nb_token + 1));
	if (!tab)
		return (0);
	tab[nb_token] = 0;
	n = 0;
	while (n < nb_token)
	{
		tab[n] = cmd_substr(line);
		if (!tab[n])
			return (free_tab(tab));
		n++;
	}
	return (tab);
}
