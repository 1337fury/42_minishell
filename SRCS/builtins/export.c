/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:08:18 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/01 16:25:27 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_value(t_env *envir, char **var)
{
	t_env	*env;

	env = get_env(var[0], envir);
	if (env)
	{
		env->value = ft_strdup(var[1]);
		env->single = false;
		return (0);
	}
	return (1);
}

void	export_ex(t_general *g_master, char **parse, char *arg)
{
	if (get_env(parse[0], g_master->exp))
		change_value(g_master->exp, parse);
	else
		insert_to_export(g_master->exp, parse, arg);
	if (get_env(parse[0], g_master->ev))
		change_value(g_master->ev, parse);
	else
		insert_to_env(g_master->ev, parse, arg);
}

void	export_ex2(t_general *g_master, char **parse, char *arg)
{
	if (!check_variable_validity(arg))
	{
		if (!get_env(parse[0], g_master->exp))
			insert_to_export(g_master->exp, parse, arg);
	}
	else if (check_variable_validity(arg))
		export_ex(g_master, parse, arg);
}

/*
- Find middle point of seperation
- Split the string using that point
- once you reach the separation point
switch to the 2nd element
*/
char	**export_split(char *arg)
{
	char	*eq;
	char	**parse;

	eq = NULL;
	if (ft_strchr(arg, '='))
		eq = ft_strchr(arg, '=');
	parse = ft_calloc(3, sizeof(char *));
	if (eq)
	{
		parse[0] = ft_substr(arg, 0, (eq - arg));
		parse[1] = ft_substr(arg, ((eq + 1) - arg),
				(ft_strlen(arg) - (eq - arg)));
	}
	else
		parse[0] = ft_strdup(arg);
	return (parse);
}

int	_export(t_general *g_master, char **arg)
{
	int		i;
	char	**parse;

	i = -1;
	if (!arg[0])
		return (print_env(g_master->exp));
	while (arg[++i])
	{
		parse = parse_variable(arg[i]);
		if (!parse)
		{
			ft_putstr_fd("export : `", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd(": is not a valid identifier\n", 2);
			builtins_exit(g_master, 1);
			return (1);
		}
		export_ex2(g_master, parse, arg[i]);
	}
	builtins_exit(g_master, 0);
	return (0);
}
