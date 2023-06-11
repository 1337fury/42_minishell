/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/11 11:40:45 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_general	g_gen;

void	_scan_table(t_row **curr)
{
	if ((*curr)->next && (*curr)->next->type > 1000)
	{
		(*curr) = (*curr)->next->next;
	}
	else
	{
		exec_family((*curr)->family);
		(*curr) = (*curr)->next;
	}
}

int	executer(t_table *table)
{
	t_row	*curr;

	if (!table)
		return (EXIT_FAILURE);
	curr = table->head;
	while (curr)
		_scan_table(&curr);
	return (EXIT_SUCCESS);
}

void	wait_for_children(bool s_w, t_family *f, int *c_p)
{
	int				s;
	int				i; 

	if (s_w)
	{
		i = -1;
		while (++i < f->size)
			waitpid(c_p[i], &s, 0);
		if (WIFEXITED(s))
			g_gen.e_status = WEXITSTATUS(s);
		else if (WIFSIGNALED(s) && WTERMSIG(s) == SIGINT)
			g_gen.e_status = WTERMSIG(s) + 128;
		g_gen.u_exec = false;
	}
}
