/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:03:19 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/02 17:29:17 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

void	pwd_builtin(void)
{
	char	buf[PATH_MAX];

	printf("%s\n", getcwd(buf, PATH_MAX));
	g_excode = 0;
}
