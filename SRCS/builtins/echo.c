/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:06:23 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/02 16:25:33 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_with_newline(t_env *home, char **arg)
{
	int	i;

	i = 1;
	(void)home;
	while (arg[i])
	{
		if (!ft_strcmp("~/", arg[i]) || !ft_strcmp("~", arg[i]))
		{
			ft_putstr_fd(home->value, 1);
			ft_putstr_fd(arg[i] + 1, 1);
		}
		else
		{
			ft_putstr_fd(arg[i], 1);
			ft_putchar_fd(' ', 1);
		}	
		i++;
	}
	printf("\n");
}

static void	print_without_newline(t_env *home, char **arg)
{
	int	i;

	i = 2;
	while (arg[i])
	{
		if (!ft_strcmp("~/", arg[i]) || !ft_strcmp("~", arg[i]))
		{
			ft_putstr_fd(home->value, 1);
			ft_putstr_fd(arg[i] + 1, 1);
			ft_putchar_fd(' ', 1);
		}
		else
		{
			ft_putstr_fd(arg[i], 1);
			ft_putchar_fd(' ', 1);
		}
		i++;
	}
}

void	_echo(t_general *g_master, char **arg)
{
	t_env	*home;

	home = get_env("HOME", g_master->ev);
	if (!arg)
	{
		ft_putchar_fd('\n', 1);
		builtins_exit(g_master, 0);
		return ;
	}
	else
	{
		if (!ft_strcmp(arg[1], "-n"))
			print_without_newline(home, arg);
		else if (ft_strcmp(arg[1], "-n"))
			print_with_newline(home, arg);
	}
	builtins_exit(g_master, 0);
}
