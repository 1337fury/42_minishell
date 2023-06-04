/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:31:31 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/04 16:03:44 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Performs lexical analysis on the given command string.
 * Checks if the command string is empty and adds it to the command history.
 * Retrieves the tokens from the command string using the `get_token` function.
 * Checks if the lexer list is clean, ensuring proper closure of parentheses and other tokens.
 * Returns the lexer list if it is clean, or NULL otherwise.
 * Prints an error message if unclosed parentheses are detected.
 */
t_list *fry_lexer(char *cmd)
{
	t_list	*list;
	
	if (!is_empty(cmd))
			add_history(cmd);
	list = get_token(cmd);
	if (!list)
		return (NULL);
	if (!is_clean(list))
	{
		g_gen.e_status = 258;
		return (NULL);
	}
	return (list);
}
