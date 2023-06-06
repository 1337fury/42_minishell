/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:31:47 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/06 16:52:16 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_malloc.h"
# include "executer.h"
# include "expander.h"
# include "lexer.h"
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <limits.h>

# define LEFT -1
# define RIGHT -2

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"

# define N_FILE "No such file or directory"
# define SYNTAX_ERROR "syntax error near unexpected token"

/*
	- `Global RULES`
*/

typedef struct s_env {
	char			*name;
	char			*value;
	bool			single;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_general
{
	char				*line;
	t_env				*ev;
	t_env				*exp;
	int					*c_procs;
	bool				u_exec;
	int					e_status;
	struct sigaction	sa;
}			t_general;

t_general	g_gen;

int		ms_errors(char *part, char *usage);
int		calc_len(t_env *env);
char	**convert_env(t_general *g_master);
int		print_env(t_env *exp);
void	imprint_env_data(char **envp, t_env *head);
t_env	*create_env(char **envp);
int		p_error(void);

int		builtins_exit(t_general *g_master, int status);
int		_change_dir(t_general *g_master, char *arg);
void	_echo(t_general *g_master, char **arg);
void	_env(t_general *g_master);
void	_exit_shell(t_general *g_master, char **arg);
int		_export(t_general *g_master, char **arg);
void	_pwd(t_general *g_master);
int		_unset(t_general *g_master, char **var);
t_env	*get_env(const char *name, t_env *env);
char	**parse_variable(char *arg);
int		check_variable_validity(char *arg);
int		insert_to_export(t_env *exp, char **var, char *arg);
int		insert_to_env(t_env *en, char **var, char *arg);
char	**export_split(char *arg);
void	export_ex2(t_general *g_master, char **parse, char *arg);
void	export_ex(t_general *g_master, char **parse, char *arg);
int		change_value(t_env *envir, char **var);

bool	process_cmdline(void);
void	init_signal_handler(void);
void	init_sig_handler_child(void);
void	reprompt(void);
void	kill_shell(void);
char	*get_env_value(char *name, t_env *env, int type);
#endif