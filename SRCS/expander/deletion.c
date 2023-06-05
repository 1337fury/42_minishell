/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/02 19:49:58 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//retrieves the nearest non-space node in a given direction
//(left or right) from a starting node in 'lexer'
t_node	*retrieve_node(t_node *curr, int direction)
{
	if (!curr)
		return (NULL);
	if (direction == LEFT)
	{
		while (curr && curr->type == SPACE)
			curr = curr->prev;
	}
	else if (direction == RIGHT)
	{
		while (curr && curr->type == SPACE)
			curr = curr->next;
	}
	return (curr);
}

// removes a node from a command lexer and adjusts
//the linked list pointers accordingly
void	destroy_node(t_list *lexer, t_node *node)
{
	t_node	*s_prev;
	t_node	*s_next;

	s_prev = node->prev;
	s_next = node->next;
	ft_lstdelone(node);
	s_prev->next = s_next;
	s_next->prev = s_prev;
	lexer->size--;
}

// removes double quotes, single quotes, left parentheses
// and right parentheses from the lexer
void	remove_dquote(t_list *lexer)
{
	t_node	*curr;
	t_node	*temp;

	curr = lexer->head;
	while (curr->type != E_CMD)
	{
		if (curr->type == DQUOTE || curr->type == SQUOTE
			|| curr->type == LEFT_PAR || curr->type == RIGHT_PAR)
		{
			temp = curr->next;
			destroy_node(lexer, curr);
			curr = temp;
			continue ;
		}
		curr = curr->next;
	}
}
