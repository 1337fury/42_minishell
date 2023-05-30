/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:41:39 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/04/07 21:42:36 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_node *lst)
{
	t_node	*node;
	int		count;

	count = 0;
	node = lst;
	while (node != NULL)
	{
		count++;
		node = node->next;
	}
	return (count);
}
