/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:54:44 by hmeftah           #+#    #+#             */
/*   Updated: 2023/05/31 18:21:18 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_non_digits(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (true);
	return (false);
}

void	exit_shell_wo_args(char	**arg)
{
	if (!arg[1])
	{
		ft_putstr_fd("exit\n", 1);
		exit (0);
	}
}

void	_exit_shell(t_general *g_master, char **arg)
{
	int	i;

	i = 0;
	exit_shell_wo_args(arg);
	while (arg[++i])
	{
		if (arg[i + 1])
			builtins_exit(g_master,
				ft_putstr_fd("exit: too many arguments\n", 2));
		else if (find_non_digits(arg[i]))
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("exit: Numeric argument required\n", 2);
			exit (255);
		}
		else
			exit (ft_atoi(arg[i]));
	}
}
