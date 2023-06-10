/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:06:23 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/10 11:59:19 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_with_newline(t_env *home, char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		reset(arg[i]);
		if (!ft_strcmp("~/", arg[i]) || !ft_strcmp("~", arg[i]))
		{
			ft_putstr_fd(home->value, 1);
			ft_putstr_fd(arg[i] + 1, 1);
		}
		else
			ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

bool	dumb_string(char *arg)
{
	int	i;

	i = 1;
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (false);
	}
	return (true);
}

static void	print_without_newline(t_env *home, char **arg)
{
	int	i;

	i = 1;
	while (arg[++i])
	{
		reset(arg[i]);
		if ((arg[i][0] == '-' && arg[i][1] == 'n' && arg[i][2] == '\0')
			|| dumb_string(arg[i]))
			continue ;
		if (!ft_strcmp("~/", arg[i]) || !ft_strcmp("~", arg[i]))
		{
			ft_putstr_fd(home->value, 1);
			ft_putstr_fd(arg[i] + 1, 1);
		}
		else
			ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
	}
}

void	_echo(t_general *g_master, char **arg)
{
	t_env	*home;

	home = get_env("HOME", g_master->ev);
	if (!arg || !arg[1])
	{
		ft_putchar_fd('\n', 1);
		builtins_exit(g_master, 0);
		return ;
	}
	else
	{
		if (arg[1] && !ft_strncmp(arg[1], "-n", ft_strlen("-n"))
			&& dumb_string(arg[1]))
			print_without_newline(home, arg);
		else if (arg[1] && ft_strcmp(arg[1], "-n"))
			print_with_newline(home, arg);
	}
	builtins_exit(g_master, 0);
}
