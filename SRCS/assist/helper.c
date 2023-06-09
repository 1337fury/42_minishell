/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:11:01 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/09 15:13:41 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_retrieve(char **exp, char *v)
{
	char	*pattern;
	t_node	*node;

	pattern = ft_substr(v, 0, _strlen(v, ' '));
	node = ft_lstnew(pattern, WILD);
	if (!ft_strcmp(pattern, "$?"))
		node->value = ft_itoa(g_gen.e_status);
	else
		wildcard_handler(node);
	*exp = ft_strjoin(*exp, node->value);
}

char	*expand_wild(char *v)
{
	char	*exp;

	exp = "";
	while (*v)
	{
		if (*v == '*' && (*(v - 1) == ' ' || !*(v - 1)))
		{
			_retrieve(&exp, v);
			v += _strlen(v, ' ') - 1;
		}
		else
			exp = ft_strjoin(exp, fry_char_to_str(*v));
		v++;
	}
	return (exp);
}

char	*get_env_value(char *name, t_env *env, int herdoc)
{
	t_env	*found;
	char	**split;

	if (ft_strchr(name, '?'))
		return (ft_itoa(g_gen.e_status));
	found = get_env(name, env);
	if (found)
	{
		if (ft_strchr(found->value, '*') && !herdoc)
			return (expand_wild(found->value));
		if (!herdoc)
		{
			split = ft_split(found->value, ' ');
			return (x_join(split));
		}
		else
			return (found->value);
	}
	else
		return (NULL);
	return (NULL);
}
