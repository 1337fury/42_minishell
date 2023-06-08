/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:30:30 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/08 12:30:52 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_exit(t_general *g_master, int status)
{
	g_master->e_status = status;
	return (status);
}

char	*x_join(char **tab)
{
	int		i;
	char	*_x;

	i = -1;
	_x = "";
	while (tab[++i])
	{
		_x = ft_strjoin(_x, tab[i]);
		_x = ft_strjoin(_x, "\x01");
	}
	return (ft_strtrim(_x, "\x01"));
}
