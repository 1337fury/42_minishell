/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:57:57 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/02 17:23:23 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_node *lst)
{
	if (!lst)
		return ;
	// EMMMMMMMMMMMM !
	// free(lst->value);
	lst->prev = NULL;
	lst->next = NULL;
	// free(lst);
}
