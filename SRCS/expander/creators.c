/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creators.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/05 15:14:31 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates a new table structure
void	create_table(t_table **table)
{
	*table = (t_table *)ft_malloc(sizeof(t_table), NULL, ALLOC, NULL);
	if (*table == NULL)
		return ;
	(*table)->head = NULL;
	(*table)->tail = NULL;
}

// Creates a new row with the specified type
t_row	*create_row(int type)
{
	t_row	*row;

	row = (t_row *)ft_malloc(sizeof(t_row), NULL, ALLOC, NULL);
	if (!row)
		return (NULL);
	row->type = type;
	row->family = NULL;
	row->prev = NULL;
	row->next = NULL;
	return (row);
}

//  Creates a new command with the specified type
t_command	*create_t_command(int type)
{
	t_command	*command;

	command = (t_command *)ft_malloc(sizeof(t_command), NULL, ALLOC, NULL);
	if (!command)
		return (NULL);
	ft_bzero(command->fds, 0);
	if (type == PIPE_CMD)
		pipe(command->fds);
	command->pos = -1;
	command->type = type;
	command->in = STDIN_FILENO;
	command->out = STDOUT_FILENO;
	command->data = NULL;
	command->prev = NULL;
	command->next = NULL;
	return (command);
}

// Initializes a new family structure
t_family	*family_init(void)
{
	t_family	*family;

	family = (t_family *)ft_malloc(sizeof(t_family), NULL, ALLOC, NULL);
	if (!family)
		return (NULL);
	family->already_seen = 0;
	family->head = NULL;
	family->tail = NULL;
	family->size = 0;
	return (family);
}
