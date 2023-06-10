/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:47:43 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/10 16:53:03 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_env(t_general *g_gen)
{
	int		i;
	char	**result;
	char	*tmp_res;
	char	*tmp_line;
	t_env	*env;

	i = 0;
	env = g_gen->ev;
	result = ft_calloc((calc_len(env) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	while (env)
	{
		tmp_line = ft_strjoin(env->name, "=");
		tmp_res = ft_strjoin(tmp_line, env->value);
		result[i++] = ft_strdup(tmp_res);
		env = env->next;
	}
	return (result);
}

int	print_env(t_env *export)
{
	t_env	*tmp;

	tmp = export;
	while (tmp)
	{
		if (tmp->single == true)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->name, 1);
			ft_putchar_fd('\n', 1);
		}
		if (tmp->single == false)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_env	*create_env(char **envp)
{
	int		i;
	char	**var;
	t_env	*head;
	t_env	*node;

	i = 0;
	head = NULL;
	if (envp[0])
	{
		var = ft_split(envp[0], '=');
		head = create_var(var[0], var[1]);
		while (envp[++i])
		{
			var = ft_split(envp[i], '=');
			node = create_var(var[0], var[1]);
			add_back(&head, node);
		}
	}
	return (head);
}

int	calc_len(t_env *env)
{
	int		len;
	t_env	*en;

	en = env;
	len = 0;
	while (en)
	{
		len++;
		en = en->next;
	}
	return (len);
}
