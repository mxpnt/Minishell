/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:24:33 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/08 14:33:57 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_init(t_data *data, char **envp)
{
	data->env = env_init(data, envp);
	data->cmds = 0;
	data->nb_cmd = 0;
	data->run = 1;
	data->error = 0;
	if (!data->env)
	{
		write(1, "minimush: init error", 20);
		data->run = 0;
	}
}

// $? pas totalement implementer
//la path est inclue dans le parsing, path[0] = 0 si path pas trouver
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	(void) argc;
	(void) argv;
	data_init(&data, envp);
	signal(SIGINT, signal_c);
	while (data.run)
	{
		line = readline("minimush$ ");
		if (line && line[0])
			add_history(line);
		if (!stcmp(line, "exit"))
		{
			write(1, "exit\n", 5);
			data.run = 0;
		}
		le_parsing(&data, line);
		if (data.cmds->cmd[0])
			pipex(data.cmds, data.env, &data);
		cmd_lstclear(&data);
		free(line);
	}
	env_lstclear(&data);
}

void	print_tab(char **tab)
{
	int	x;

	if (!tab)
		return ;
	x = 0;
	while (tab[x])
	{
		printf("%s\n", tab[x]);
		x++;
	}
}
