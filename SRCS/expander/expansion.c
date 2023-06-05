/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/05 15:14:59 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_general	g_gen;

// Expands variables and concatenates adjacent string nodes into a single node
t_node	*basic_expander(t_list *lexer, t_node *curr)
{
	if (curr && curr->type == VAR)
	{
		if (retrieve_node(curr->prev, LEFT)->type == HERDOC)
			return (curr->type = STR, curr);
		else
		{
			curr->value = get_env_value(curr->value + 1, g_gen.exp);
			if (!curr->value)
				curr->value = ft_strdup("");
		}
	}
	while (curr && curr->next
		&& (curr->next->type == STR || curr->next->type == VAR))
	{
		if (curr->next->type == STR)
		{
			curr->value = ft_strjoin(curr->value, curr->next->value);
			destroy_node(lexer, curr->next);
		}
		else if (curr->next->type == VAR)
		{
			if (retrieve_node(curr->prev, LEFT)->type != HERDOC)
			{
				curr->next->value
					= get_env_value(curr->next->value + 1, g_gen.exp);
				if (!curr->next->value)
					curr->next->value = ft_strdup("");
			}
			curr->value = ft_strjoin(curr->value, curr->next->value);
			destroy_node(lexer, curr->next);
		}
	}
	return (curr);
}
