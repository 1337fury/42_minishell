/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:09:31 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/01/02 12:16:20 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_m(char *s, char c)
{
	int	l;

	l = 0;
	while (s[l] && s[l] != c)
		l++;
	return (l);
}

int	ft_strchr_m(char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (1)
	{
		if (s[i] == c)
			return (1);
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

char	*ft_strlcpy_m(char *dest, char *src, int len)
{
	int	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_m(char *s1, char *s2)
{
	char	*rs;
	int		s1_len;
	int		s2_len;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen_m(s1, '\0');
	s2_len = ft_strlen_m(s2, '\0');
	rs = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!rs)
		return (NULL);
	ft_strlcpy_m(rs, s1, s1_len);
	ft_strlcpy_m(rs + s1_len, s2, s2_len);
	rs[s1_len + s2_len] = '\0';
	free(s1);
	return (rs);
}

char	*ft_del_oldline(char *temp)
{
	char	*rs;
	int		l_len;
	int		t_len;
	int		i;

	l_len = ft_strlen_m(temp, '\n');
	if (!temp[l_len])
	{
		free(temp);
		return (NULL);
	}
	t_len = ft_strlen_m(temp, '\0');
	rs = (char *)malloc(sizeof(char) * (t_len - l_len + 1));
	if (!rs)
		return (NULL);
	l_len++;
	i = 0;
	while (l_len < t_len)
		rs[i++] = temp[l_len++];
	rs[i] = '\0';
	free(temp);
	return (rs);
}
