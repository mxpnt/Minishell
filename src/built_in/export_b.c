/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:27:53 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/23 17:04:59 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_excode;

static t_env	*env_cpy_new(t_env env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(env.name);
	if (env.value)
		new->value = ft_strdup(env.value);
	new->next = NULL;
	return (new);
}

static t_env	*env_cpy(t_env *env)
{
	t_env	*cpy;
	t_env	*node;
	int		i;

	i = 0;
	cpy = NULL;
	while (env)
	{
		node = env_cpy_new((*env));
		env_lstadd_back(&cpy, node);
		env = env->next;
	}
	return (cpy);
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
		if (stcmp(curr->name, save->name) == 0)
		{
			if (!prev)
				root = curr->next;
			else
				prev->next = curr->next;
			free(curr->name);
			if (curr->value)
				free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	(*cpy) = root;
}

static void	ft_which_env(t_env **cpy)
{
	t_env	*save;
	t_env	*root;

	root = *cpy;
	save = *cpy;
	while ((*cpy))
	{
		if (stcmp(save->name, (*cpy)->name) > 0)
			save = *cpy;
		(*cpy) = (*cpy)->next;
	}
	(*cpy) = root;
	if (save->value)
		printf("declare -x %s=\"%s\"\n", save->name, save->value);
	else
		printf("declare -x %s\n", save->name);
	lst_clear_one_env(cpy, save);
}

void	export_builtin(t_data *data)
{
	t_env	*cpy;
	int		i;
	int		nb_env;

	cpy = env_cpy(data->env);
	nb_env = ft_nb_env(data->env);
	if (!data->cmds->cmd[1])
	{
		i = -1;
		while (++i < nb_env)
			ft_which_env(&cpy);
	}
	else
	{
		i = 0;
		while (data->cmds->cmd[++i])
			ft_add_env(data->cmds->cmd[i], data);
	}
	g_excode = 0;
}