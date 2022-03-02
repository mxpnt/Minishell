/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:37:47 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/02 17:35:34 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

int	check_env_char(char *line, int y)
{
	while ((line[y] >= 'a' && line[y] <= 'z')
		|| (line[y] >= 'A' && line[y] <= 'Z')
		|| (line[y] >= '0' && line[y] <= '9'))
		y++;
	return (y);
}

char	*search_env(t_env *env, char *line)
{
	int	x;

	x = 0;
	if (line[x] == '?')
		return (ft_itoa(g_excode));
	x = check_env_char(line, x);
	while (env && x)
	{
		if (!ft_strncmp(line, env->name, x) && stlen(env->name) == x)
			return (env->value);
		env = env->next;
	}
	return (0);
}

char	*insert_value(char *line, int *x, int dq, char *value)
{
	int	y;

	y = *x + 1;
	if (!line[y] || is_spe_env(line[y], dq))
		*x = *x + 1;
	else if (!dq && (line[y] == '\'' || line[y] == '"'))
		ft_strcpy(line + *x, line + y);
	else if (line[y] >= '0' && line[y] <= '9')
		ft_strcpy(line + *x, line + y + 1);
	else
	{
		if (line[y] == '?')
			y++;
		else
			y = check_env_char(line, y);
		ft_strcpy(line + *x, line + y);
		if (value)
		{
			line = put_value(line, *x, value, line[*x + 1]);
			*x += stlen(value);
		}
	}
	return (line);
}

int	replace_env_line(t_env *env, char **old_line)
{
	int		x;
	int		dq;
	char	*line;

	x = 0;
	dq = 0;
	line = *old_line;
	while (line[x])
	{
		if (line[x] == '\'' && !dq)
			x = skip_quote(line, x);
		if (line[x] == '"')
			dq = (dq + 1) % 2;
		if (line[x] == '$')
		{
			line = insert_value(line, &x, dq, search_env(env, line + x + 1));
			if (!line)
				return (1);
			*old_line = line;
		}
		else
			x++;
	}
	return (0);
}
