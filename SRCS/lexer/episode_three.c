/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   episode_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:31:31 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/06 13:08:53 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FOR THE NORM
void	_else(t_list *lexer, t_scanner *point, char *c)
{
	ft_lstadd_back(&lexer->head, ft_lstnew(fry_char_to_str(c[0]), STR));
	point->current++;
}

/**
 * Handles operators in the given string, including logical operators
 * (|| and &&),
 * redirection operators (>>, <<), and single character operators (|, >, <).
 * Adds appropriate nodes to the lexer list based on the encountered operator.
 * Also updates the current position.
 */
void	operator_handler(t_list *lexer, t_scanner *point, char *cmd)
{
	char	c[2];
	int		type;

	c[0] = cmd[point->current];
	c[1] = cmd[point->current + 1];
	if (c[0] == '|' && c[1] == '|')
		ft_lstadd_back(&lexer->head, ft_lstnew(ft_strdup("||"), OR));
	else if (c[0] == '>' && c[1] == '>')
		ft_lstadd_back(&lexer->head, ft_lstnew(ft_strdup(">>"), APPEND));
	else if (c[0] == '<' && c[1] == '<')
		ft_lstadd_back(&lexer->head, ft_lstnew(ft_strdup("<<"), HERDOC));
	else if (c[0] == '&' && c[1] == '&')
		ft_lstadd_back(&lexer->head, ft_lstnew(ft_strdup("&&"), AND));
	else if (c[0] != '&')
	{
		type = (c[0] == '|') * PIPE + (c[0] == '>')
			* GREAT + (c[0] == '<') * LESS;
		ft_lstadd_back(&lexer->head, ft_lstnew(fry_char_to_str(c[0]), type));
		point->current++;
		return ;
	}
	else
		return (_else(lexer, point, c));
	point->current += 2;
}

/**
 * Handles default cases in the given string, where characters
 * are not special characters or operators.
 * Advances the current position until a special character,
 * operator, or whitespace is encountered.
 * Creates a new node in the lexer list with the extracted value
 * indicating whether it contains a wildcard or not.
 */
void	default_handler(t_list *lexer, t_scanner *point, char *cmd)
{
	bool	wildcard;
	char	*value;

	wildcard = false;
	while (cmd[point->current] && !ft_strchr("\'\"$()<|&>",
			cmd[point->current]) && !is_space(cmd[point->current]))
	{
		if (cmd[point->current] == '*')
			wildcard = true;
		point->current++;
	}
	value = ft_substr(cmd, point->start, point->current - point->start);
	if (wildcard)
		ft_lstadd_back(&lexer->head, ft_lstnew(value, WILD));
	else
		ft_lstadd_back(&lexer->head, ft_lstnew(value ,STR));
}
