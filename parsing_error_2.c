/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:01:43 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/17 16:19:37 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_error(t_data *data, char c)
{
	char	s[2];

	if (c == 0)
		return (mess_error(data, 0, "newline", 0));
	s[0] = c;
	s[1] = 0;
	return (mess_error(data, c, 0, 0));
}

int	wrong_redcara(t_data *data, char *line)
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
		return (red_error(data, c));
	return (0);
}
