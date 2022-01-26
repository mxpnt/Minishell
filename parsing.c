/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:02:28 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/26 14:49:37 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_parsing(t_data *data, char **line_split)
{
	int		x;
	t_cmd	*t;

	x = 0;
	while (line_split[x])
	{
		t = cmd_lstnew(data);
		if (!t)
			return (cmd_lstclear(data));
		cmd_lstadd_back(&data->cmds, t);
		if (replace_env_line(data->env, &line_split[x]))
			return (cmd_lstclear(data));
		if (red_parsing(data, t, line_split[x]))
			return (cmd_lstclear(data));
		t->cmd = ft_split(line_split[x], ' ');
		if (!t->cmd && check_if_only_space(line_split[x]))
			return (cmd_lstclear(data));
		x++;
	}
	data->nb_cmd = x;
	return (0);
}

int	le_parsing(t_data *data, char *line)
{
	char	**line_split;

	if (!line || check_quote_n_pipe(data, line) || check_red(data, line))
		return (1);
	line_split = pipe_split(line);
	if (!line_split)
		return (mess_error(data, 0, 0, 1));
	if (cmd_parsing(data, line_split))
	{
		free_tab(line_split);
		return (mess_error(data, 0, 0, 1));
	}
	free_tab(line_split);
	return (0);
}
