/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:53:57 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/02 13:13:17 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell_struct.h"

// ft_itoa.c
char			*ft_itoa(long long int n);

// ft_split.c
char			**ft_split(char const *s, char c);

// megajoin.c
char			*megajoin(int n, ...);

// stock_1.c
int				stcmp(const char *s1, const char *s2);
int				stlen(const char *s);
char			*ft_substr(char const *s, int start, int len);
char			*ft_strdup(const char *s1);
char			**free_tab(char	**tab);

// stock_2.c
char			*ft_strjoin(char *s1, char *s2);
int				skip_quote(char *line, int x);
void			ft_strcpy(char *dst, const char *src);
void			ft_strcat(char *dst, const char *src);
int				ft_strncmp(const char *s1, const char *s2, int n);

// stock_3.c
int				tablen(char **tab);
void			write_nl(int fd, char *s);
void			red_remove_quote(char *s);
int				longest_in_tab(char **tab);
short			satoi(char *str);

// stock_4.c
char			*ft_lower_case(char *str);
char			*ft_strrchr(const char *s, int c);
char			*ft_userchr(t_data *data);

// stock_5.c
int				is_number(char *str);
long long int	atolli(char *str);
int				ft_nb_env(t_env *env);
void			change_value_env(char *str, t_env *env);
int				check_equal(char *str);

#endif