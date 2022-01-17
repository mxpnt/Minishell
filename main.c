/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:24:33 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/16 15:23:49 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_init(t_data *data, char **envp)
{
	data->env = env_init(data, envp);
	data->cmds = 0;
	data->run = 1;
	data->error = 0;
	if (!data->env)
	{
		write(1, "minimush: init error", 20);
		data->run = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	(void) argc;
	(void) argv;
	data_init(&data, envp);
	while (data.run)
	{
		line = readline("minimush$ ");
		if (line[0])
			add_history(line);
		le_parsing(&data, line);
		free(line);
	}
	env_lstclear(&data);
}
