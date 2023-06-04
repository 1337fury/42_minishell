/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/04 16:13:30 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Updates the lexer by expanding variables, removing spaces, and handling wildcards
t_list	*update_lexer(t_list *lexer)
{
	t_node	*curr;
	t_node	*next;

	curr = lexer->head;
	while (curr->type != E_CMD)
	{
		if (curr->type == STR || curr->type == VAR)
			curr = basic_expander(lexer, curr);
		if (curr->type == SPACE)
		{
			next = curr->next;
			destroy_node(lexer, curr);
			curr = next;
			continue ;
		}
		if (curr->type == WILD)
		{
			if (curr->prev && !(curr->prev->type % 3))
			{
				curr->type = WILD;
				curr = curr->next;
			}
			else
				curr = wildcard_handler(curr);
		}
		else
			curr = curr->next;
	}
	return (lexer);
}
// Expands and processes the lexer to create a table of commands
t_table	*fry_expander(t_list *lexer)
{
	t_table	*expander;
	t_node	*curr;

	if (!lexer)
		return (NULL);
	create_table(&expander);
	if (!expander)
		return (NULL);
	remove_dquote(lexer);
	lexer = update_lexer(lexer);
	curr = lexer->head;
	if (!curr || curr->type == E_CMD)
		return (NULL);
	while (curr->type != E_CMD)
	{
	    if (!(curr->type % 3) || !(curr->type % 2) || curr->type == PIPE)
	        table_add_back(&expander, build_command(&curr));
	    else if (curr->type == AND || curr->type == OR)
	    {
			table_add_back(&expander, create_row((curr->type == AND) * \
				AND + (curr->type == OR) * OR));
			curr = curr->next;
	    }
	    else
	        curr = curr->next;
	}
	return (expander);
}
