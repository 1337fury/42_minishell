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

static void	delete_variable(t_env *env, char *var)
{
	t_env	*found;
	t_env	*prev;
	t_env	*next;

	found = env;
	prev = NULL;
	next = NULL;
	while (found->next)
	{
		if (!ft_strcmp(found->next->name, var))
			prev = found;
		else if (!ft_strcmp(found->name, var))
		{
			next = found->next;
			// free (found->name);
			// free (found->value);
			// free (found);
			prev->next = next;
			return ;
		}
		found = found->next;
	}
}

void	print_unset_error(char *var)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not valid identifier \n", 2);
}

void	_unset(t_general *g_master, char **var)
{
	int	i;
	int	j;

	i = -1;
	while (var[++i])
	{
		if (!ft_isalpha(var[i][0]))
		{
			print_unset_error(var[i]);
			builtins_exit(g_master, 1);
			return ;
		}
		j = -1;
		while (var[i][++j])
		{
			if (!ft_isalnum(var[i][j]))
			{
				print_unset_error(var[i]);
				builtins_exit(g_master, 1);
				return ;
			}
		}
		delete_variable(g_master->ev, var[i]);
		delete_variable(g_master->exp, var[i]);
		builtins_exit(g_master, 0);
	}
}
