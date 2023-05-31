/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/31 18:39:25 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_general	g_gen;

int	_redirector_builtins(t_command *cmd, int *fd)
{
	if (cmd->in == -1 || cmd->out == -1)
	{
		builtins_exit(&g_gen, 1);
		return (/*ms_errors("open", "no such file or directory !"),*/ 1);
	}
	if (cmd->out != 1)
	{
		fd[1] = dup(STDOUT_FILENO);
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	return (EXIT_SUCCESS);
}

void	restore_fd(int *fd, t_command *cmd)
{
	if (cmd->out != 1)
		dup2(fd[1], STDOUT_FILENO);
}

void	exec_builtins(t_command *cmd, bool pipe)
{
	int	fd[2];

	if (!pipe)
		_redirector_builtins(cmd, fd);
	if (!ft_strncmp(cmd->data[0], "echo", ft_strlen(cmd->data[0])))
		_echo(&g_gen, cmd->data);
	else if (!ft_strncmp(cmd->data[0], "cd", ft_strlen(cmd->data[0])))
		_change_dir(&g_gen, cmd->data[1]);
	else if (!ft_strncmp(cmd->data[0], "export", ft_strlen(cmd->data[0])))
		_export(&g_gen, cmd->data + 1);
	else if (!ft_strncmp(cmd->data[0], "env", ft_strlen(cmd->data[0])))
		_env(&g_gen);
	else if (!ft_strncmp(cmd->data[0], "unset", ft_strlen(cmd->data[0])))
		_unset(&g_gen, cmd->data + 1);
	else if (!ft_strncmp(cmd->data[0], "pwd", ft_strlen(cmd->data[0])))
		_pwd(&g_gen);
	else if (!ft_strncmp(cmd->data[0], "exit", ft_strlen(cmd->data[0])))
		_exit_shell(&g_gen, cmd->data);
	else if (!ft_strncmp(cmd->data[0], "echo", ft_strlen(cmd->data[0])))
		_echo(&g_gen, cmd->data + 1);
	if (!pipe)
		restore_fd(fd, cmd);
}
