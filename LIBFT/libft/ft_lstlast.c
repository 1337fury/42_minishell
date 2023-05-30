/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:10:19 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/04/07 21:43:08 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstlast(t_node *lst)
{
	t_node	*node;

	node = lst;
	while (node != NULL)
	{
		if (node->next == NULL)
			return (node);
		node = node->next;
	}
	return (node);
}
