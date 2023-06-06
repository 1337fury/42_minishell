/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:11:01 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/06 18:16:34 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	p_error(void)
{
	perror(strerror(errno));
	return (1);
}

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

char	*get_env_value(char *name, t_env *env, int herdoc)
{
	t_env	*found;
	char	**split;

	if (ft_strchr(name, '?'))
		return (ft_itoa(g_gen.e_status));
	found = get_env(name, env);
	if (found)
	{
		if (!herdoc)
		{
			split = ft_split(found->value, ' ');
			return (x_join(split));
		}
		return (found->value);
	}
	else
		return (NULL);
	return (NULL);
}
