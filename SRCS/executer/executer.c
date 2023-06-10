/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/10 16:03:09 by hmeftah          ###   ########.fr       */
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

void	wait_for_children(t_family *f, int *c_p, int *s_w)
{
	int	i;
	int	status;

	if (*s_w)
	{
		g_gen.u_exec = true;
		i = 0;
		while (i < f->size)
		{
			if (waitpid(c_p[i], &status, 0) == -1)
				perror(strerror(errno));
			if (WIFSIGNALED(status))
				g_gen.e_status = 128 + WTERMSIG(status);
			else if (WIFEXITED(status))
				g_gen.e_status = WEXITSTATUS(status);
			i++;
		}
		g_gen.u_exec = false;
	}
}
