/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:37:47 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/21 13:26:54 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_char(char c)
{
	if (!c || c == ' ' || c == '\'' || c == '"')
		return (1);
	return (0);
}

char	*search_env(t_env *env, char *line)
{
	int	x;

	x = 0;
	while (!check_env_char(line[x]))
		x++;
	while (env)
	{
		if (!ft_strncmp(line, env->name, x))
			return (env->value);
		env = env->next;
	}
	return (0);
}

char	*insert_env_value(char *line, int x, int dq, char *value)
{
	return (line);
}

int	replace_env_line(t_env *env, char **add_line)
{
	int		x;
	int		dq;
	char	*line;

	x = 0;
	dq = 0;
	line = *add_line;
	while (line[x])
	{
		if (line[x] == '\'')
			x = skip_quote(line, x);
		if (line[x] == '"')
			dq = (dq + 1) % 2;
		if (line[x] == '$')
		{
			line = insert_env_value(line, x, dq, search_env(env, line + x + 1));
			if (!line)
				return (1);
			*add_line = line;
		}
		else
			x++;
	}
	return (0);
}

void	remove_wrong_env(char *line)
{
	int	x;
	int	n;
	int	dq;

	x = 0;
	while (line[x])
	{
		if (line[x] == '\'')
			x = skip_quote(line, x);
		if (line[x] == '"')
			dq = (dq + 1) % 2;
		if (line[x] == '$')
		{
			n = 1;//check_wong_env(line + x);
		}
		else
			x++;
	}
}
