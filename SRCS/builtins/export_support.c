/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:15:32 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/09 16:12:31 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Finds Variables in export list,
returns a pointer to the variable if found, returns NULL if else*/
t_env	*get_env(const char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!name)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**parse_variable(char *arg)
{
	int		i;
	char	**result;

	i = 0;
	if (!arg || (arg[0] != '_' && !ft_isalpha(arg[0])))
		return (NULL);
	result = export_split(arg);
	while (result[0][++i])
	{
		if (arg[i] != '_' && !ft_isalnum(result[0][i]))
			return (NULL);
	}
	return (result);
}

int	check_variable_validity(char *arg)
{
	if (!ft_strchr(arg, '='))
		return (0);
	else
		return (1);
	return (1);
}

int	insert_to_export(t_env *exp, char **var, char *arg)
{
	t_env	*env;
	t_env	*tmp;

	tmp = exp;
	while (tmp)
	{
		env = tmp;
		tmp = tmp->next;
	}
	tmp = env;
	tmp->next = (t_env *)ft_malloc(sizeof(t_env), NULL, ALLOC, NULL);
	tmp->next->name = ft_strdup(var[0]);
	tmp->next->single = true;
	if (ft_strchr(arg, '='))
		tmp->next->single = false;
	if (!var[1])
		tmp->next->value = ft_strdup("");
	else
		tmp->next->value = ft_strdup(var[1]);
	tmp->next->prev = tmp;
	tmp->next->next = NULL;
	return (0);
}

int	insert_to_env(t_env *en, char **var, char *arg)
{
	t_env	*env;
	t_env	*tmp;

	tmp = en;
	while (tmp)
	{
		env = tmp;
		tmp = tmp->next;
	}
	tmp = env;
	tmp->next = (t_env *)ft_malloc(sizeof(t_env), NULL, ALLOC, NULL);
	tmp->next->name = ft_strdup(var[0]);
	tmp->next->single = true;
	if (ft_strchr(arg, '='))
		tmp->next->single = false;
	if (!var[1])
		tmp->next->value = ft_strdup("");
	else
		tmp->next->value = ft_strdup(var[1]);
	tmp->next->prev = tmp;
	tmp->next->next = NULL;
	return (0);
}
