/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:31:31 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/11 14:03:23 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_value(char *f_name)
{
	int	i;

	i = 0;
	if (!f_name || !ft_strcmp(f_name, "\x02") || !ft_strcmp(f_name, ""))
		return (0);
	while (f_name && f_name[i])
	{
		if (f_name[i] == '\x01')
			return (0);
		i++;
	}
	return (1);
}

int	check_next(t_node *n)
{
	char	*f_name;

	if (n->type == VAR)
	{
		f_name = ft_strtrim(get_env_value(n->value + 1, g_gen.exp, false), "\x01");
		return (check_value(f_name));
	}
	return (1);
}

int	ambiguous(t_list *lst, bool *am)
{
	t_node	*curr;
	t_node	*n;

	curr = lst->head;
	while (curr->type != E_CMD)
	{
		n = retrieve_node(curr->next, RIGHT);
		if (!(curr->type % 3) && !(curr->type == 9))
		{
			if (!check_next(n))
			{
				*am = true;
				return (ms_errors(n->value, "ambiguous redirect"), 0);
			}
		}
		curr = curr->next;
	}
	return (true);
}

/**
 * Performs lexical analysis on the given command string.
 * Checks if the command string is empty and adds it to the command history.
 * Retrieves the tokens from the command string using the `get_token` function.
 * Checks if the lexer list is clean, ensuring proper closure of
 * parentheses and other tokens.
 * Returns the lexer list if it is clean, or NULL otherwise.
 * Prints an error message if unclosed parentheses are detected.
 */
t_list	*fry_lexer(char *cmd)
{
	t_list	*list;
	bool	ambi;

	if (!is_empty(cmd))
		add_history(cmd);
	list = get_token(cmd);
	if (!list)
		return (NULL);
	ambi = false;
	if (!is_clean(list) || !ambiguous(list, &ambi))
	{
		if (ambi)
			g_gen.e_status = 1;
		else
			g_gen.e_status = 258;
		return (NULL);
	}
	return (list);
}
