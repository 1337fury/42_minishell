/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:30:30 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/09 15:19:37 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_general	g_gen;

int	builtins_exit(t_general *g_master, int status)
{
	if (!g_gen.f_open)
		g_master->e_status = status;
	g_gen.f_open = false;
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
