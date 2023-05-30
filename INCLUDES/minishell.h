/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:31:47 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/30 16:14:59 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

#include "executer.h"

#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#define ERR_SQUOTE "unclosed single quotes"
#define ERR_DQUOTE "unclosed double quotes"

#define LEFT -1
#define RIGHT -2
#define N_LINE 10

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"

/*
	- `Global RULES`
*/

typedef struct s_envp
{
	char	**env_vars;
	int		size;
}	t_envp;

typedef struct s_general
{
	t_envp	*envp;
	int		e_status;
}			t_general;

t_general	g_gen;

void	ms_errors(char *part, char *usage/*, int ex_status*/);

#endif