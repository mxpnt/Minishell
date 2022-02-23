/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:24:33 by lsuau             #+#    #+#             */
/*   Updated: 2022/02/23 17:19:33 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	data_init(t_data *data, char **envp)
{
	data->env = env_init(data, envp);
	data->cmds = 0;
	data->nb_cmd = 0;
	data->run = 1;
	if (tcgetattr(0, &data->term_base) == -1)
	{
		perror("tcgetattr");
		data->run = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	char	*test;

	(void) argc;
	(void) argv;
	data_init(&data, envp);
	while (data.run)
	{
		signal_handler();
		test = set_prompt(&data);
		line = readline(test);
		if (!line)
			exit(0); // fonction exit_ctrld
		if (line && line[0])
			add_history(line);
		le_parsing(&data, line);
		if (data.nb_cmd)
			pipex(data.cmds, data.env, &data);
		cmd_lstclear(&data);
		free(line);
		free(test);
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
