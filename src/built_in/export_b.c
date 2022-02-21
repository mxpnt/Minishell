/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:27:53 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/21 17:21:12 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_nb_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static t_env	*env_cpy(char **envp)
{
	t_env	*env;
	t_env	t;
	int		x;

	env = NULL;
	x = 0;
	while (envp[x])
	{
		t = env_lstnew(envp[x]);
		env_lstadd_back(&env, t);
		x++;
	}
	return (env);
}

static void	lst_clear_one_env(t_env **cpy, t_env *save)
{
	t_env	*prev;
	t_env	*curr;
	t_env	*root;

	curr = *cpy;
	root = *cpy;
	prev = NULL;
	while (curr)
	{
		dprintf(1, "@@@@@@@@@@@@@@@@@@@@@@@\n%s === %s\n", curr->name, save->name);
		if (stcmp(curr->name, save->name) == 0)
		{
			if (!prev)
				root = curr->next;
			else
				prev->next = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	dprintf(1, ">>>>>>>>>>>>>>>>%s=%s\n", root->name, root->value);
	*cpy = root;
	dprintf(1, "$$$$$$$$$$$$$$$$%s=%s\n", (*cpy)->name, (*cpy)->value);
}

static void	ft_which_env(t_env *cpy)
{
	t_env	*save;
	t_env	*root;

	root = cpy;
	save = cpy;
	dprintf(1, "========================================\n");
	while (cpy)
	{
		if (stcmp(save->name, cpy->name) > 0)
			save = cpy;
		printf("==== %s=\"%s\"\n", cpy->name, cpy->value);
		cpy = cpy->next;
	}
	cpy = root;
	// printf("declare -x %s=\"%s\"\n", save->name, save->value);
	dprintf(1, "+++++++++++++++++++++++++++\n%s=\"%s\"\n", save->name, save->value);
	lst_clear_one_env(&cpy, save);
}

// faire une vraie copie et non une copie de pointeur
void	export_builtin(t_data *data)
{
	t_env	*cpy;
	int		i;
	int		nb_env;

	cpy = env_cpy(data->cmds->envp);
	i = -1;
	nb_env = ft_nb_env(data->env);
	if (!data->cmds->cmd[1])
	{
		while (++i < nb_env)
			ft_which_env(cpy);
	}
}
