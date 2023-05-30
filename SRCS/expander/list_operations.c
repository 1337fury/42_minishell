/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/26 20:23:45 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adds a new row to the end of the table
void	 table_add_back(t_table **expander, t_row *new_row)
{
	if (!expander || !new_row)
		return ;
	if ((*expander)->tail)
	{
		new_row->prev = (*expander)->tail;
		(*expander)->tail->next = new_row;
		(*expander)->tail = new_row;
		return ;
	}
	(*expander)->head = new_row;
	(*expander)->tail = new_row;
}
// Adds a new command to the end of the family
void	family_add_back(t_family **family, t_command *new_cmd)
{
	if ((*family)->tail)
	{
		new_cmd->prev = (*family)->tail;
		(*family)->tail->next = new_cmd;
		(*family)->tail = new_cmd;
		(*family)->size +=1;
		return ;
	}
	(*family)->head = new_cmd;
	(*family)->tail = new_cmd;
	(*family)->size +=1;
}
