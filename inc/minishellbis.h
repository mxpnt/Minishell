/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellbis.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:17:45 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/05 13:40:21 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLBIS_H
# define MINISHELLBIS_H

# include <fcntl.h>
# include <signal.h>
# include "minishell_struct.h"

# ifndef BMAG
#  define BMAG "\e[1;35m"
# endif
# ifndef CRESET
#  define CRESET "\e[0m"
# endif
# ifndef BRED
#  define BRED "\e[1;31m"
# endif
# ifndef BORA
#  define BORA "\e[1;34m"
# endif

extern int	g_excode;

// pipex.c
void			pipex(t_cmd *cmd, t_env *env, t_data *data);
void			ft_exec(t_cmd *cmd, t_data *data);
void			last_cmd(t_cmd *cmd, t_data *data);
void			one_cmd(t_cmd *cmd, t_data *data);

// excode.c
void			wait_excode(int pid, int status);

// parsing_path_cmd.c
char			**get_path_env_splited(t_env *env, t_cmd *cmd);
char			*parsing_path(t_cmd *cmd, t_env *env);

// perror_exit.c
void			ft_perror_exit(const char *str, int code);
void			ft_command_not_found(const char *str);

// handle_redirect.c
void			ft_handle_redirect_out(t_cmd *cmd);
void			ft_handle_redirect_in(t_cmd *cmd);

// execute.c
void			le_exec(t_cmd *cmd, t_env *env, t_data *data);

// handle_builtins.c
int				is_builtin(char *str);
void			which_builtin(t_cmd *cmd, t_data *data, int n);
int				handle_builtin(t_cmd *cmd, t_data *data);

// echo_b.c
void			echo_builtin(t_cmd *cmd);

// pwd_b.c
void			pwd_builtin(t_env *env);

// env_b.c
void			env_builtin(t_env *env);

// exit_b.c
void			exit_builtin(t_data *data);

// export_b.c
void			export_builtin(t_data *data);

// export2_b.c
void			ft_add_env(char *str, t_data *data);

// unset_b.c
void			unset_builtin(t_cmd *cmd, t_env **env);

// cd_b.c
void			cd_builtin(t_cmd *cmd);

// stock_2.c
char			*ft_strjoin(char *s1, char *s2);

// stock_4.c
char			*ft_lower_case(char *str);
int				last_char_is_bs(char *str);
char			*clean_bs(char *str);
char			*ft_strrchr(const char *s, int c);
char			*ft_userchr(t_data *data);

// stock_5.c
int				is_number(char *str);
long long int	atolli(char *str);
void			change_value_env(char *str, t_env *env);
int				check_equal(char *str);

// ft_split.c
char			**ft_split(char const *s, char c);

// megajoin.c
char			*megajoin(int n, ...);

// signal.c
void			signal_c(int signum);
void			signal_handler(void);
void			signal_child(int signum);
void			signal_child_handler(t_data *data);
void			sig_her(int signum);

// prompt.c
char			*set_prompt(t_data *data);

#endif