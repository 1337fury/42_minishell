/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:10:55 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/31 20:10:25 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_node	*ft_lstnew(char *value, int type)
{
	t_node	*new_node;

	new_node = (t_node *)ft_malloc(sizeof(t_node), NULL, ALLOC, NULL);
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->value = value;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}
