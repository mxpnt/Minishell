/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:30:25 by lsuau             #+#    #+#             */
/*   Updated: 2022/01/19 16:41:56 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_lstadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*bl;

	bl = *alst;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next)
		*alst = (*alst)->next;
	(*alst)->next = new;
	*alst = bl;
}

int	cmd_lstclear(t_data *data)
{
	t_cmd	*l;
	t_cmd	*t;

	l = data->cmds;
	while (l)
	{
		t = l->next;
		if (l->cmd)
			free_tab(l->cmd);
		if (l->path)
			free(l->path);
		if (l->in)
			free(l->in);
		if (l->out)
			free(l->out);
		if (l->envp)
			free_tab(l->envp);
		free(l);
		l = t;
	}
	return (1);
}

char	**env_lst_to_tab(t_env *env)
{
	char	**envp;
	char	*t;
	int		x;

	x = 0;
	envp = malloc(sizeof(char) * (env_lstsize(env) + 1));
	if (!envp)
		return (0);
	while (env)
	{
		t = ft_strjoin(env->name, "=");
		envp[x] = ft_strjoin(t, env->value);
		if (t)
			free(t);
		if (!envp[x])
			return (free_tab(envp));
		x++;
		env = env->next;
	}
	envp[x] = 0;
	return (0);
}

t_cmd	*cmd_lstnew(t_data *data)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->cmd = 0;
	new->path = 0;
	new->in = 0;
	new->out = 0;
	new->envp = env_lst_to_tab(data->env);
	new->next = 0;
	if (!new->envp)
	{
		free(new);
		return (0);
	}
	return (new);
}
