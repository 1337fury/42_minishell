/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_episode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:31:31 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/05 15:20:58 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates and returns a new empty linked list with a head and tail set to NULL.
t_list	*create_list(void)
{
	t_list	*lst;

	lst = (t_list *)ft_malloc(sizeof(t_list), NULL, ALLOC, NULL);
	if (!lst)
		return (NULL);
	lst->size = 0;
	lst->head = NULL;
	lst->tail = NULL;
	return (lst);
}

/* Converts a single character to a new string
	and returns a pointer to that string.
*/
char	*fry_char_to_str(char c)
{
	char	*result;

	if (!c)
		return (NULL);
	result = (char *)ft_malloc(2 * sizeof(char), NULL, ALLOC, NULL);
	if (!result)
		return (NULL);
	result[0] = c;
	result[1] = '\0';
	return (result);
}
