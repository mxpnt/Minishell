/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:37:47 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/23 16:26:44 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_env_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*search_env(t_env *env, char *line)
{
	int	x;

	x = 0;
	if (line[x] == '?')
		x++;
	else
	{
		while (check_env_char(line[x]))
			x++;
	}
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
		while (check_env_char(line[y]))
			y++;
		ft_strcpy(line + *x, line + y);
		if (value)
		{
			line = put_value(line, *x, value);
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
