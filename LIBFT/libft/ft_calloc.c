/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:05:55 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/31 20:03:05 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*dest;
	size_t	s;

	if (size >= SIZE_MAX && count >= SIZE_MAX)
		return (0);
	s = count * size;
	dest = (char *)ft_malloc(s, NULL, ALLOC, NULL);
	if (!dest)
		return (NULL);
	ft_memset(dest, 0, s);
	return (dest);
}
//The calloc() function contiguously allocates enough space for count objects
//that are size bytes of memory each and returns a pointer to the 
//allocated memory. The allocated memory is filled with bytes of value zero.