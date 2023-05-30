/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:01:09 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/02/13 11:21:57 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_strlen_m(char *s, char c);
int		ft_strchr_m(char *s, char c);
char	*ft_strjoin_m(char *s1, char *s2);
char	*ft_strlcpy_m(char *dest, char *src, int len);
char	*get_next_line(int fd);
char	*ft_reader(int fd, char *temp);
char	*ft_line_extractor(char	*temp);
char	*ft_del_oldline(char *temp);

#endif