/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:45:05 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/01 16:25:39 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_variable(t_env **env, char *var)
{
	t_env	*found;

	found = get_env(var, *env);
	if (found)
	{
		if (found->prev)
			found->prev->next = found->next;
		else
		{
			*env = found->next;
			found->next->prev = NULL;
		}
	}
}

int	print_unset_error(char *var)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not valid identifier \n", 2);
	return (1);
}

int	_unset(t_general *g_master, char **var)
{
	int	i;
	int	j;

	i = -1;
	while (var[++i])
	{
		if (var[i][0] != '_' && !ft_isalpha(var[i][0]))
			return (builtins_exit(g_master, print_unset_error(var[i])));
		j = 0;
		while (var[i][++j])
			if (!ft_isalnum(var[i][j]) && var[i][j] != '_')
				return (builtins_exit(g_master, print_unset_error(var[i])));
		delete_variable(&g_master->ev, var[i]);
		delete_variable(&g_master->exp, var[i]);
		builtins_exit(g_master, 0);
	}
	return (0);
}
