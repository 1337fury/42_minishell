/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:06:32 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/01 16:25:19 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_node(t_env *env, char *name, char *value)
{
	t_env	*tmp;
	t_env	*last;

	tmp = env;
	while (tmp)
	{
		last = tmp;
		tmp = tmp->next;
	}
	tmp = last;
	tmp->next = (t_env *)ft_malloc(sizeof(t_env), NULL, ALLOC, NULL);
	tmp->next->name = ft_strdup(name);
	tmp->next->value = ft_strdup(value);
	tmp->next->next = NULL;
}

void	update_last_pwd(t_env *env)
{
	char	cwddir[PATH_MAX];

	getcwd(cwddir, PATH_MAX);
	get_env("PWD", env)->value = ft_strdup(cwddir);
}

void	find_and_insert_oldpwd(t_env *export, t_env *env, char *odir)
{
	if (!get_env("OLDPWD", env))
	{
		insert_node(export, "OLDPWD", odir);
		insert_node(env, "OLDPWD", odir);
	}
	else
	{
		if (ft_strcmp(get_env("OLDPWD", env)->value, odir))
		{
			get_env("OLDPWD", env)->value = ft_strdup(odir);
			get_env("OLDPWD", export)->value = ft_strdup(odir);
		}
	}
}

void	update_pwd(t_general *g_master, char *old_dir)
{
	find_and_insert_oldpwd(g_master->ev, g_master->exp, old_dir);
	update_last_pwd(g_master->exp);
	update_last_pwd(g_master->ev);
}

int	_change_dir(t_general *g_master, char *arg)
{
	t_env	*home;
	char	*dir;
	char	old_dir[PATH_MAX];

	home = get_env("HOME", g_master->ev);
	getcwd(old_dir, PATH_MAX);
	if (!arg)
	{
		if (chdir(home->value) == -1)
			return (builtins_exit(g_master, ms_errors("cd", N_FILE)));
	}
	else if ((arg[0] == '~' && arg[1] == '/') || (arg[0] == '~' && !arg[1]))
	{
		dir = "/";
		dir = ft_strjoin(home->value, arg + 1);
		if (chdir(dir) == -1)
			return (builtins_exit (g_master, ms_errors("cd", N_FILE)));
	}
	else
		if (chdir(arg) == -1)
			return (builtins_exit (g_master, ms_errors("cd", N_FILE)));
	update_pwd(g_master, old_dir);
	return (builtins_exit(g_master, 0));
}
