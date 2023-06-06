/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   episode_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:31:31 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/06 12:12:15 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(t_bit *word, t_list *lexer, t_scanner *point, char *cmd)
{
	int		point_stop;
	t_bit	empty;

	empty.is = false;
	if (cmd[point->current] == '$')
	{
		if (word->is)
		{
			point_stop = point->current - point->start;
			ft_lstadd_back(&lexer->head,
				ft_lstnew(ft_substr(cmd, point->start, point_stop), STR));
			point->start = point->current;
		}
		dollar_handler(lexer, point, cmd);
		point->start = point->current;
		word->is = false;
	}
	else
	{
		word->is = true;
		point->current++;
	}
}

/**
 * Handles double quotes in the given string, extracting variable names and
 * updating the lexer list accordingly.
 * If a valid variable name is found, it invokes the `dollar_handler`
 * function to handle it.
 * Also checks for errors and updates the current position.
 */
void	dquote_handler(t_list *lexer, t_scanner *point, char *cmd)
{
	int		point_stop;
	t_bit	empty;
	t_bit	word;

	ft_lstadd_back(&lexer->head, ft_lstnew(ft_strdup("\""), DQUOTE));
	point->current++;
	empty.is = true;
	word.is = false;
	while (cmd[point->current] && cmd[point->current] != '\"')
		handler(&word, lexer, point, cmd);
	point_stop = point->current - point->start;
	if (word.is)
		ft_lstadd_back(&lexer->head,
			ft_lstnew(ft_substr(cmd, point->start, point_stop), STR));
	if (empty.is)
		ft_lstadd_back(&lexer->head, ft_lstnew(ft_strdup("\x02"), EMPTY));
	if (cmd[point->current] == '"')
		ft_lstadd_back(&lexer->head, ft_lstnew(ft_strdup("\""), DQUOTE));
	point->current++;
}

/**
 * Handles parentheses in the given string, determining whether it is a
 * left parenthesis or a right parenthesis.
 * Creates a new node in the lexer list with the appropriate type based on
 * the encountered parenthesis.
 * Also updates the current position.
 */
void	par_handler(t_list *lexer, t_scanner *point, char *cmd)
{
	int		type;
	char	*value;

	if (cmd[point->current] == '(')
		type = LEFT_PAR;
	else
		type = RIGHT_PAR;
	point->current++;
	value = ft_substr(cmd, point->start, point->current - point->start);
	ft_lstadd_back(&lexer->head, ft_lstnew(value, type));
}
