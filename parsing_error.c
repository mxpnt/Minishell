/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:30:04 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/16 15:21:03 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mess_error(t_data *data, int n)
{
	data->error = 1;
	if (n == 0)
		write(2, "minimush: syntax error\n", 23);
	else if (n == 1)
		write(1, "minimush: malloc error\n", 23);
	return (1);
}

//check if there is blank between pipe
int	check_pipe(char *line, int sq, int dq)
{
	int	x;

	x = 0;
	if (line[x] != '|' || sq || dq)
		return (0);
	x++;
	while (line[x] == ' ')
		x++;
	if (!line[x] || line[x] == '|')
		return (1);
	return (0);
}

int	check_first_pipe(char *line)
{
	int	x;

	x = 0;
	while (line[x] == ' ')
		x++;
	if (line[x] == '|')
		return (1);
	return (0);
}

//check if all quotes are closed and pipe correct
int	check_quote_n_pipe(char *line)
{
	int	x;
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	x = 0;
	while (line[x])
	{
		if (line[x] == '\'' && !(dq % 2))
			sq++;
		else if (line[x] == '"' && !(sq % 2))
			dq++;
		else if (check_pipe(line + x, sq % 2, dq % 2))
			return (1);
		x++;
	}
	if (sq % 2 || dq % 2 || check_first_pipe(line))
		return (1);
	return (0);
}

int	check_red(char *line)
{
	int	x;
	int	quote[2];

	quote[0] = 0;
	quote[1] = 0;
	x = 0;
	while (line[x])
	{
		if (line[x] == '\'' && !(quote[1] % 2))
			quote[0]++;
		else if (line[x] == '"' && !(quote[0] % 2))
			quote[1]++;
		if (!((quote[0] % 2) + (quote[1] % 2)) && (line[x] == '>' || line[x] == '<'))
		{
			if (wrong_redcara(line + x))
				return (1);
		}	
		x++;
	}
	return (0);
}
	