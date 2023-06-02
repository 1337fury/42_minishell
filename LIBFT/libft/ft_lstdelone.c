/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:57:57 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/02 17:46:10 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*ft_malloc(0, lst->value, FREE, 0);
ft_malloc(0, lst->value, FREE, 0);*/

void	ft_lstdelone(t_node *lst)
{
	if (!lst)
		return ;
	lst->prev = NULL;
	lst->next = NULL;
}
