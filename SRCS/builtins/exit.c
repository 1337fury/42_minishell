/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:54:44 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/09 18:19:08 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_non_digits(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '+' || str[i] == '-')
			i++;
		if (!ft_isdigit(str[i]))
			return (true);
	}
	return (false);
}

void	exit_shell_wo_args(char	**arg)
{
	if (!arg[1])
		exit (0);
}

void	_exit_shell(t_general *g_master, char **arg)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	exit_shell_wo_args(arg);
	while (arg[++i])
	{
		if (find_non_digits(arg[i]))
		{
			ft_putstr_fd("exit: Numeric argument required\n", 2);
			ft_malloc(0, NULL, FREE_ALL, NULL);
			exit (255);
		}
		else if (arg[i + 1])
		{
			builtins_exit(g_master,
				ft_putstr_fd("exit: too many arguments\n", 2));
			return ;
		}
		else
		{
			ft_malloc(0, NULL, FREE_ALL, NULL);
			exit (ft_atoi(arg[i]));
		}
	}
}
