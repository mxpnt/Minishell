/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:50:04 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/18 10:55:40 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	in_x2_name(t_cmd *cmd)
{
	static int	x;
	char		*t;
	char		*n;

	t = ft_strdup("temp_infile_");
	n = ft_itoa(x);
	cmd->in = ft_strjoin(t, n);
	if (t)
		free(t);
	if (n)
		free(n);
	x++;
	cmd->red_in = 1;
	return ;
}

void	heredoc_fork(t_env *env, char *name, char *del)
{
	char	*s;
	int		fd;

	if (name)
		fd = open(name, O_CREAT | O_WRONLY, 0644);
	while (1)
	{
		s = readline("> ");
		if (!stcmp(s, del))
		{
			free(s);
			break ;
		}
		if (replace_env_line(env, &s))
			exit(1);
		if (name)
			write_nl(fd, s);
		free(s);
	}
	if (name)
		close(fd);
	exit (0);
}

int	heredoc_red(t_data *data, t_cmd *cmd, char *in, int n)
{
	int	pid;
	int	status;

	signal_child_handler(data);
	if (!n)
	{
		in_x2_name(cmd);
		if (!cmd->in)
			return (1);
	}
	pid = fork();
	if (pid < 0)
		return (mess_error(0, 0, 3));
	if (pid == 0)
		heredoc_fork(data->env, cmd->in, in);
	while (waitpid(pid, &status, 0) != -1)
		;
	return (0);
}
