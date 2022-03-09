/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:17:55 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/09 18:58:38 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	in_x1_red(t_cmd *cmd, char *in, int n)
{
	if (access(in, F_OK) || access(in, R_OK))
	{
		cmd->in = ft_strdup(in);
		if (!cmd->in)
			return (1);
		cmd->red_in = -1;
		return (-1);
	}
	if (!n)
	{
		cmd->in = ft_strdup(in);
		if (!cmd->in)
			return (1);
	}
	return (0);
}

int	out_no_perm(t_cmd *cmd, char *out)
{
	cmd->red_out = -1;
	cmd->out = ft_strdup(out);
	return (-1);
}

void	out_no_file(t_cmd *cmd, char *out, int n)
{
	int	fd;

	fd = open(out, O_CREAT, 0644);
	close(fd);
	if (!n)
		cmd->out = ft_strdup(out);
}

int	remove_red(char *out)
{
	if (out[1] == '>')
	{
		ft_strcpy(out, out + 2);
		return (1);
	}
	ft_strcpy(out, out + 1);
	return (0);
}
