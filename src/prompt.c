/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:23:17 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/16 09:07:29 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*set_prompt(t_data *data)
{
	char		*prompt;
	char		buf[PATH_MAX];
	t_prompt	elem;

	elem.status = "🏵  ";
	getcwd(buf, PATH_MAX);
	elem.curr_dir = ft_strrchr(buf, '/') + 1;
	elem.user = ft_userchr(data);
	prompt = megajoin(10, elem.status, BMAG, elem.curr_dir, BORA, " user:(", \
			BRED, elem.user, BORA, ") ", CRESET);
	if (elem.user)
		free(elem.user);
	if (!prompt)
		prompt = ft_strdup("minimush$ ");
	return (prompt);
}
