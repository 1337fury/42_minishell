/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backstage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:31:31 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/04 12:51:28 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the current position has reached
// or exceeded the end of the given string.
bool	is_at_end(int *current, char *cmd)
{
	return ((size_t) * current >= ft_strlen(cmd));
}

// Retrieves the character at the current position
// in the given string and advances the position.
char	advance(char *cmd, int *current)
{
	return (cmd[*current++]);
}

/**
 * Scans and processes a single token in the given string
 * updating the lexer list accordingly.
 * Determines the type of token based on the encountered character and invokes
 * the corresponding handler function.
 * Also updates the current position and lexer size.
 */
void	scan_token(t_list **lexer, char *cmd, t_scanner *point)
{
	char	c;

	c = advance(cmd, &point->current);
	if (is_space(c))
		spaces_handler(*lexer, &point->current, cmd);
	else if (c == '\'')
	{
		point->start++;
		squote_handler(*lexer, point, cmd);
	}
	else if (c == '\"')
	{
		point->start++;
		dquote_handler(*lexer, point, cmd);
	}
	else if (c == '$')
		dollar_handler(*lexer, point, cmd);
	else if (c == '(' || c == ')')
		par_handler(*lexer, point, cmd);
	else if (ft_strchr("<|&>", c))
		operator_handler(*lexer, point, cmd);
	else
		default_handler(*lexer, point, cmd);
	(*lexer)->size++;
}

/**
 * Retrieves tokens from the given command string and builds a lexer list
 * containing the tokens.
 * It scans the command string character by character, invoking the
 * appropriate token scanning functions.
 * Returns the lexer list containing the tokens.
 */
t_list	*get_token(char *cmd)
{
	t_list		*lexer;
	t_scanner	point;

	lexer = create_list();
	if (!lexer)
		return (NULL);
	point.start = 0;
	point.current = 0;
	ft_lstadd_back(&(lexer->head), ft_lstnew(NULL, S_CMD));
	while (!is_at_end(&point.current, cmd))
	{
		point.start = point.current;
		scan_token(&lexer, cmd, &point);
	}
	ft_lstadd_back(&(lexer->head), ft_lstnew(NULL, E_CMD));
	lexer->size += 2;
	return (lexer);
}
