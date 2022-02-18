/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:42:23 by mapontil          #+#    #+#             */
/*   Updated: 2022/02/16 10:58:58 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_perror_exit(const char *str, int code)
{
	if (code > 0)
		errno = code;
	write(1, "minishell: ", 11);
	perror(str);
	exit(errno);
}

// a implementer
void	ft_command_not_found(const char *str)
{
	printf("minishell: %s: command not found\n", str);
	exit(127);
}
