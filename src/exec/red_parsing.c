/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:46:26 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/18 10:53:17 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	process_in(t_cmd *cmd, char **in, t_data *data)
{
	int	x;
	int	r;
	int	last;

	last = tablen(in) - 1;
	x = 0;
	while (last >= 0 && in[x])
	{
		if (in[x][1] == '<')
		{
			if (heredoc_red(data, cmd, in[x] + 2, last - x))
				return (1);
		}
		else
		{
			r = in_x1_red(cmd, in[x] + 1, last - x);
			if (r == 1)
				return (1);
			else if (r == -1)
				last = 0;
		}
		x++;
	}
	return (0);
}

void	empty_redout(char *out)
{
	int	fd;

	fd = open(out, O_WRONLY | O_TRUNC);
	close(fd);
}

int	process_out(t_cmd *cmd, char **out)
{
	int	x;
	int	r;
	int	last;

	last = tablen(out) - 1;
	x = 0;
	while (out[x] && last >= 0)
	{
		cmd->red_out = remove_red(out[x]);
		if (!access(out[x], F_OK))
		{
			if (access(out[x], W_OK))
				last = out_no_perm(cmd, out[x]);
			else if (x == last)
				cmd->out = ft_strdup(out[x]);
			else if (!cmd->red_out)
				empty_redout(out[x]);
		}
		else
			out_no_file(cmd, out[x], last - x);
		x++;
	}
	if (last >= 0 && !cmd->out)
		return (1);
	return (0);
}

int	red_parsing(t_data *data, t_cmd	*cmd, char *line)
{
	char	**in;
	char	**out;

	in = fill_red_tab(line, '<');
	out = fill_red_tab(line, '>');
	if ((!out && red_count(line, '>')) && (!in && red_count(line, '<')))
	{
		free_tab(in);
		free_tab(out);
		return (1);
	}
	if (process_in(cmd, in, data))
		return (1);
	if (process_out(cmd, out))
		return (1);
	free_tab(in);
	free_tab(out);
	return (0);
}
