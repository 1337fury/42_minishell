/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:47:43 by hmeftah           #+#    #+#             */
/*   Updated: 2023/05/31 18:29:56 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_env(t_general *g_master)
{
	int		i;
	char	**result;
	char	*tmp_res;
	char	*tmp_line;
	t_env	*env;

	i = 0;
	env = g_master->ev;
	result = ft_calloc(calc_len(env) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (env->next)
	{
		tmp_line = ft_strjoin(env->name, "=");
		tmp_res = ft_strjoin(tmp_line, env->value);
		result[i++] = ft_strdup(tmp_res);
		free(tmp_line);
		free(tmp_res);
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

void	imprint_env_data(char **envp, t_env *head)
{
	t_env	*temp;
	char	**hold;
	int		i;

	temp = head;
	i = 0;
	while (envp[i])
	{
		hold = ft_split(envp[i], '=');
		temp->name = ft_strdup(hold[0]);
		temp->value = ft_strdup(hold[1]);
		//free_2d_array(hold);
		temp = temp->next;
		i++;
	}
}

t_env	*create_env(char **envp)
{
	t_env	*head;
	t_env	*temp;
	t_env	*prev;
	int		i;

	i = 0;
	head = (t_env *)ft_calloc(1, sizeof(t_env));
	head->prev = NULL;
	temp = head;
	while (envp[i + 1])
	{
		prev = temp;
		temp->single = false;
		temp->next = (t_env *)ft_calloc(1, sizeof(t_env));
		temp = temp->next;
		temp->prev = prev;
		i++;
	}
	temp->next = NULL;
	imprint_env_data(envp, head);
	return (head);
}

int	calc_len(t_env *env)
{
	int		len;
	t_env	*en;

	en = env;
	len = 0;
	while (en->next)
	{
		len++;
		en = en->next;
	}
	return (len);
}
