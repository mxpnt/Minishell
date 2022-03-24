/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:41:11 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/23 16:32:07 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	space_between(char *s)
{
	int	x;

	x = 0;
	while (s[x] == ' ')
		x++;
	while (s[x] && s[x] != ' ')
		x++;
	while (s[x] == ' ')
		x++;
	if (s[x])
		return (1);
	return (0);
}

int	check_ambiguous(t_cmd *cmd, char **tab)
{
	int		n;
	char	*t;

	n = 0;
	while (tab[n])
	{
		t = ft_strdup(tab[n]);
		replace_env_line(cmd->data->env, &t);
		if (space_between(t) && ft_strncmp(tab[n], "<<", 2))
		{
			free(t);
			cmd->red_in = -2;
			cmd->in = ft_strdup(tab[n]);
			return (1);
		}
		free(t);
		n++;
	}
	return (0);
}
