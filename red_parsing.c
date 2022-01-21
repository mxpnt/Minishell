/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:46:26 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/19 16:37:12 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	//process_in(cmd, in);
	//print_tab(in);
	//print_tab(out);
	return (0);
}
