/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:02:28 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/17 13:49:14 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	cmd_parsing(t_data *data, char **line_split)
{
	int		x;
	t_cmd	*t;

	x = 0;
	while (line_split[x])
	{
		t = malloc(sizeof(t_cmd));
		if (!t || red_parsing(data, t, line_split[x]))
			return (1);
	}
	return (0);
}*/

int	le_parsing(t_data *data, char *line)
{
	char	**line_split;

	if (check_quote_n_pipe(line) || check_red(line))
		return (mess_error(data, 0));
	line_split = pipe_split(line);
	if (!line_split)
		return (mess_error(data, 1));
	/*if (cmd_parsing(data, line_split))
	{
		free_tab(line_split);
		return (mess_error(data, 1));
	}*/
	free_tab(line_split);
	return (0);
}
