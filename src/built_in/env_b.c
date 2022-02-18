/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:13:26 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/14 09:04:17 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_builtin(t_env *env)
{
	char	*str;

	while (env)
	{
		str = ft_strjoin(env->name, "=");
		str = ft_strjoin(str, env->value);
		write(1, str, stlen(str));
		write(1, "\n", 1);
		env = env->next;
	}
}
