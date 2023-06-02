/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_episode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:31:31 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/02 19:56:23 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates and returns a new empty linked list with a head and tail set to NULL.
t_list	*create_list(void)
{
	t_list	*lst;

	lst = (t_list *)ft_malloc(sizeof(t_list), NULL, ALLOC, NULL);
	if (!lst)
		return (NULL);
	lst->size = 0;
	lst->head = NULL;
	lst->tail = NULL;
	return (lst);
}

/* Converts a single character to a new string
	and returns a pointer to that string.
*/
char	*fry_char_to_str(char c)
{
	char	*result;

	if (!c)
		return (NULL);
	result = (char *)ft_malloc(2 * sizeof(char), NULL, ALLOC, NULL);
	if (!result)
		return (NULL);
	result[0] = c;
	result[1] = '\0';
	return (result);
}

/**
 * Checks whether parentheses in the given
 * linked list of nodes are properly closed.
 * Counts the number of left and right parentheses
 * encountered while traversing the list.
 * Returns true if the number of right
 * parentheses matches the number of left parentheses,
 * indicating proper closure. Otherwise, returns false.
 */
bool	is_closed(t_node *curr)
{
	int	sin;
	int	doub;

	sin = 0;
	doub = 0;
	while (curr != NULL)
	{
		if (curr->type == SQUOTE)
			sin++;
		else if (curr->type == DQUOTE)
			doub++;
		curr = curr->next;
	}
	if (doub % 2 || sin % 2)
		return (false);
	return (true);
}

bool	c_op(t_node *r, t_node *l)
{
	if (r->type == E_CMD || r->type == RIGHT_PAR || !(r->type % 5))
		return (ms_errors("fry@shell",
				"syntax error near unexpected token"), false);
	else if (l->type == S_CMD || l->type == LEFT_PAR || !(r->type % 5))
		return (ms_errors("fry@shell",
				"syntax error near unexpected token"), false);
	return (true);
}

bool	c_red(t_node *r)
{
	if (!(r->type % 5) || !(r->type % 7) || !(r->type % 3) || r->type == E_CMD)
		return (ms_errors("fry@shell",
				"syntax error near unexpected token"), false);
	return (true);
}

bool	c_par(int type, t_node *r, t_node *l)
{
	(void)l;
	if (type == RIGHT_PAR)
	{
		if (!(r->type % 2))
			return (ms_errors("fry@shell",
					"syntax error near unexpected token"), false);
	}
	else
	{
		if (!(r->type % 5) || !(l->type % 2))
			return (ms_errors("fry@shell",
					"syntax error near unexpected token"), false);
	}
	return (true);
}

/**
 * Checks whether the given lexer list is clean, meaning it has proper closure of parentheses and other tokens.
 * Calls the `is_closed` function to check if parentheses are properly closed.
 * Returns true if the lexer list is clean, and false otherwise.
 */
// [%3 : REDIRECTION] [%5 : operator] [%7 : parentheses] [%2 : string]
bool	is_clean(t_list *list)
{
	t_node	*curr;
	t_node	*n;
	t_node	*p;
	bool	status;

	status = true;
	curr = list->head;

	if (!is_closed(curr))
		return (ms_errors("syntax error", "unclosed quotes"), false);
	while (curr->type != E_CMD)
	{
		n = retrieve_node(curr->next, RIGHT);
		p = retrieve_node(curr->prev, LEFT);
		if (!(curr->type % 3))
			status = c_red(n);
		else if (curr->type == LEFT_PAR || curr->type == RIGHT_PAR)
			status = c_par(curr->type, n, p);
		else if (!(curr->type % 5))
			status = c_op(n, p);
		if (!status)
			return (false);
		curr = curr->next;
	}
	return (true);
}
