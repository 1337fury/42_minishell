/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:21:51 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/04/07 21:44:26 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_node **lst)
{
	t_node	*suivant;

	suivant = *lst;
	if (!lst)
		return ;
	while (*lst != NULL)
	{
		suivant = suivant->next;
		free(*lst);
		*lst = suivant;
	}
	*lst = NULL;
}
