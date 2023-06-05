/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_strjoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:37:23 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/01 16:24:36 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Concatenates two strings, s1 and s2, with a space character in between.
char	*join_with_space(char *s1, char *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
	{
		s1 = (char *)ft_malloc(sizeof(char) * 1, NULL, ALLOC, NULL);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = ft_malloc(1 * (s1_len + s2_len + 1 + 1), NULL, ALLOC, NULL);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, s1_len);
	ft_memcpy(res + s1_len, " ", 1);
	ft_memcpy(res + s1_len + 1, s2, s2_len);
	res[s1_len + 1 + s2_len] = '\0';
	return (res);
}
