/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:08:52 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/21 13:24:54 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	char		*phaystack;
	char		*pneedle;

	phaystack = (char *)haystack;
	pneedle = (char *)needle;
	if (!phaystack && !len)
		return (NULL);
	if (pneedle[0] == '\0')
		return (phaystack);
	while (*phaystack && len)
	{
		i = 0;
		while (phaystack[i] != '\0' && phaystack[i] == pneedle[i]
			&& phaystack[i] != ',')
			i++;
		if (pneedle[i] == '\0' && phaystack[i] == ',')
			return (phaystack);
		phaystack++;
		len--;
	}
	return (NULL);
}

/*
{=1=}  The strnstr() function locates the first occurrence of the null-terminated
string needle in the string haystack,
where not more than len characters are searched. 
Characters that appear after a `\0'character are not searched.  
Since the strnstr() function is a FreeBSD specific API,
it should only be used when portability is not a concern.
*/
