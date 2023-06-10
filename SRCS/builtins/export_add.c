/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:02:24 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/10 16:27:12 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_var(char *name, char *value)
{
	t_env	*node;

	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	node->prev = NULL;
	node->next = NULL;
	if (value)
	{
		node->single = false;
		node->value = ft_strdup(value);
	}
	else
	{
		node->single = true;
		node->value = ft_strdup("");
	}
	return (node);
}

void	add_back(t_env **env, t_env *node)
{
	t_env	*tmp;

	tmp = *env;
	if (*env == NULL)
	{
		*env = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}
