/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_line_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:52:53 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/08 16:23:21 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	is_spe_env(char c, int dq)
{
	int	n;

	n = 1;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		n = 0;
	if ((c >= '0' && c <= '9'))
		n = 0;
	if ((c == '"' && !dq) || c == '?')
		n = 0;
	return (n);
}

char	*put_value(char *line, int x, char *value)
{
	char	*s;
	int		i;
	int		y;

	s = malloc(sizeof(char) * (stlen(line) + stlen(value) + 3));
	if (!s)
		return (0);
	i = -1;
	while (++i < x)
		s[i] = line[i];
	s[i] = '"';
	y = -1;
	while (value[++y])
		s[i + y + 1] = value[y];
	s[i + y + 1] = '"';
	y++;
	while (line[i])
	{
		s[i + y + 1] = line[i];
		i++;
	}
	s[i + y + 1] = 0;
	free(line);
	return (s);
}
