/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/27 07:55:46 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// /usr/bin/sort | /bin/cat | /usr/bin/grep Makefile

// void	exec_comp(t_row *row)
// {
// 	printf("ROW IS LOGICAL\n");
// 	exit (0);
// }

void	_scan_table(t_row **curr)
{
	if ((*curr)->next && (*curr)->next->type > 1000)
	{
		// exec_comp(*curr);
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
