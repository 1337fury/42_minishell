/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   episode_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:31:31 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/31 15:19:56 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Handles spaces in the given string, advancing the position until a newline or non-space character is encountered.
 * If spaces were encountered, adds a new node with the SPACE type to the lexer list.
 */
void	spaces_handler(t_list *lexer, int *current, char *cmd)
{
	t_bit	enter;

	enter.is = 0;
	while (cmd && cmd[*current] != N_LINE && is_space(cmd[*current]))
	{
		enter.is = 1;
		(*current)++;
	}
	if (enter.is)
		ft_lstadd_back(&(lexer->head), ft_lstnew(NULL, SPACE));
}

/**
 * Handles single quotes in the given string, updating the lexer list accordingly.
 * If a single quote is found, it adds appropriate nodes to the lexer list.
 * Also checks for errors and updates the current position.
 */
void	squote_handler(t_list *lexer, t_scanner *point, char *cmd)
{
	t_bit	enter;
	char	*value;

	enter.is = 0;
	ft_lstadd_back(&(lexer->head), ft_lstnew(ft_strdup("\'"), SQUOTE));
	point->current++;
	while (cmd[point->current] && cmd[point->current] != '\'' && cmd[point->current] != N_LINE)
	{
		enter.is = 1;
		point->current++;
	}
	if (enter.is)
	{
		value = ft_substr(cmd, point->start, point->current - point->start);
		ft_lstadd_back(&(lexer->head), ft_lstnew(value, STR));
	}
	if (cmd[point->current] != '\'')
		ms_errors("syntax error", "enclosed quotes");
	ft_lstadd_back(&lexer->head, ft_lstnew(ft_strdup("\'"), SQUOTE));
	point->current++;
}
/**
 * Handles dollar signs in the given string, extracting variable names and updating the lexer list accordingly.
 * If a valid variable name or special character sequence is found, it adds appropriate nodes to the lexer list.
 * Also updates the current position.
 */
void	dollar_handler(t_list *lexer, t_scanner *point, char *cmd)
{
	char	*value;
	t_bit	enter;

	if (cmd[point->current + 1] && cmd[point->current + 1] == '?')
	{
		point->current += 2;
		value = ft_substr(cmd, point->start, point->current - point->start);
		ft_lstadd_back(&lexer->head, ft_lstnew(value, VAR));
		return ;
	}
	enter.is = 0;
	while (cmd[point->current + 1] && (cmd[point->current + 1] == '_' || ft_isalnum(cmd[point->current + 1])))
	{
		enter.is = 1;
		point->current++;
	}
	point->current++;
	if (enter.is)
	{
		value = ft_substr(cmd, point->start, point->current - point->start);
		ft_lstadd_back(&lexer->head, ft_lstnew(value, VAR));
	}
	else
		ft_lstadd_back(&lexer->head, ft_lstnew(ft_strdup("$"), STR));
}
