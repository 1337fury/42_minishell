/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:54:13 by hmeftah           #+#    #+#             */
/*   Updated: 2023/05/31 18:23:52 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env(t_general *g_master)
{
	t_env	*temp;

	temp = g_master->ev;
	while (temp)
	{
		if (temp->value)
		{
			ft_putstr_fd(temp->name, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(temp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		temp = temp->next;
	}
	builtins_exit(g_master, 0);
}
