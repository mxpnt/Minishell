/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:18:15 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/16 15:35:41 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_count(char	*line, char c)
{
	int	x;
	int	nb_char;
	int	quote[2];

	nb_char = 1;
	quote[0] = 0;
	quote[1] = 0;
	x = 0;
	while (line[x])
	{
		if (line[x] == '\'' && !(quote[1] % 2))
			quote[0]++;
		else if (line[x] == '"' && !(quote[0] % 2))
			quote[1]++;
		else if (!((quote[0] % 2) + (quote[1] % 2)) && line[x] == c)
			nb_char++;
		x++;
	}
	return (nb_char);
}

int	next_pipe(char *line, int n)
{
	int	x;
	int	pipe;
	int	quote[2];

	quote[0] = 0;
	quote[1] = 0;
	pipe = 0;
	x = 0;
	if (n == -1)
		return (0);
	while (line[x])
	{
		if (line[x] == '\'' && !(quote[1] % 2))
			quote[0]++;
		else if (line[x] == '"' && !(quote[0] % 2))
			quote[1]++;
		else if (!((quote[0] % 2) + (quote[1] % 2)) && line[x] == '|')
		{
			if (pipe == n)
				return (x + 1);
			pipe++;
		}
		x++;
	}
	return (x + 1);
}

char	**pipe_split(char *line)
{
	char	**spl;
	char	*t;
	int		nb_cmd;
	int		x;

	x = 0;
	nb_cmd = char_count(line, '|');
	spl = malloc(sizeof(char *) * (nb_cmd + 1));
	if (!spl)
		return (0);
	spl[nb_cmd] = 0;
	while (x < nb_cmd)
	{
		t = ft_substr(line, next_pipe(line, x - 1), \
			next_pipe(line, x) - next_pipe(line, x - 1) - 1);
		spl[x] = t;
		if (!t)
			return (free_tab(spl));
		x++;
	}
	return (spl);
}

int	wrong_redcara(char *line)
{
	int		x;
	char	red;
	char	c;

	x = 1;
	if (line[0] == line[1])
		x = 2;
	red = line[0];
	while (line[x] == ' ')
		x++;
	c = line[x];
	if (c == '|' || c == 0 || c == '>' || c == '<')
		return (1);
	return (0);
}
