/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:08:18 by hmeftah           #+#    #+#             */
/*   Updated: 2023/05/30 20:39:09 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_value(t_env *envir, char **var)
{
	t_env	*env;

	env = get_env(var[0], envir);
	if (env)
	{
		if (env->value)
			free(env->value);
		env->value = ft_strdup(var[1]);
		return (0);
	}
	//free_2d_array(var);
	return (1);
}

void	export_ex(t_general *g_master, char **parse, char *arg)
{
	if (get_env(parse[0], g_master->exp))
	{
		change_value(g_master->ev, parse);
		change_value(g_master->exp, parse);
	}
	else
	{
		insert_to_env(g_master->ev, parse, arg);
		insert_to_export(g_master->exp, parse, arg);
	}
	//free_2d_array(parse);
}

void	export_ex2(t_general *g_master, char **parse, char *arg)
{
	if (!check_variable_validity(arg))
	{
		if (get_env(parse[0], g_master->exp))
			change_value(g_master->exp, parse);
		else
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
	char	**parse;
	char	*first;
	int		j;
	int		f_el;
	int		i;

	i = -1;
	f_el = -1;
	first = ft_strchr(arg, '=');
	parse = ft_calloc(3, sizeof(char *));
	if (!parse)
		return (NULL);
	while (++f_el <= 1)
	{
		j = 0;
		parse[f_el] = ft_calloc(ft_strlen(arg), sizeof(char));
		while (arg[++i])
		{
			if (&arg[i] == first)
				break ;
			parse[f_el][j++] = arg[i];
		}
	}
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
