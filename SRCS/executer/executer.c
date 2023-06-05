/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/30 19:42:46 by hmeftah          ###   ########.fr       */
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

void	wait_for_children(bool s_w, int *i_e, t_family *f, int *c_p)
{
	if (s_w)
	{
		g_gen.u_exec = true;
		i_e[0] = -1;
		while (++i_e[0] < f->size)
			waitpid(c_p[i_e[0]], &i_e[1], 0);
		g_gen.e_status = WEXITSTATUS(i_e[1]);
		g_gen.u_exec = false;
	}
}
