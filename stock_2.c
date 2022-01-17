/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:46:04 by mapontil          #+#    #+#             */
/*   Updated: 2022/01/17 15:46:21 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	size_t	size1;
	size_t	size2;
	size_t	i;

	if (!s1)
		return (0);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	dst = malloc((size1 + size2 + 1) * sizeof(char));
	if (!dst)
		return (0);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	i = -1;
	while (s2[++i])
		dst[size1 + i] = s2[i];
	dst[size1 + size2] = '\0';
	return (dst);
}
