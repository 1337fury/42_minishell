/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:09:15 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/01/31 16:52:59 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_reader(int fd, char *temp)
{
	int		status;
	char	*buffer;	

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	status = 1;
	while (ft_strchr_m(temp, '\n') == 0 && status != 0)
	{
		status = read(fd, buffer, BUFFER_SIZE);
		if (status == -1)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		buffer[status] = '\0';
		temp = ft_strjoin_m(temp, buffer);
	}
	free(buffer);
	return (temp);
}

char	*ft_line_extractor(char	*temp)
{
	char	*rs;
	int		l;
	int		i;

	i = 0;
	if (!temp[i])
		return (NULL);
	l = ft_strlen_m(temp, '\n');
	rs = (char *)malloc((l + 2) * sizeof(char));
	if (!rs)
		return (NULL);
	while (temp[i] && temp[i] != '\n')
	{
		rs[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
		rs[i] = temp[i];
		i++;
	}
	rs[i] = '\0';
	return (rs);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;

	if (fd > 4096 || BUFFER_SIZE <= 0 || fd == 1 || fd == 2)
		return (0);
	temp = ft_reader(fd, temp);
	if (!temp)
		return (NULL);
	line = ft_line_extractor(temp);
	temp = ft_del_oldline(temp);
	return (line);
}
