/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:56:10 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/01 16:25:34 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_pwd(t_general *g_master)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, PATH_MAX);
	ft_putstr_fd(dir, 1);
	// free (dir);
	builtins_exit(g_master, 0);
}
