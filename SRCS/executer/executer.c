/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/10 17:02:43 by abdeel-o         ###   ########.fr       */
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
	int	s;
	int	i;

	i = -1;
	g_gen.u_exec = true;
	if (s_w)
	{
	    while (++i < f->size)
			waitpid(c_p[0], &s, 0);
		if (WIFEXITED(s))
			g_gen.e_status = WEXITSTATUS(s);
		else if (WIFSIGNALED(s) && WTERMSIG(s) == SIGINT)
			g_gen.e_status = WTERMSIG(s) + 128;
	    g_gen.u_exec = false;
	}
}
