/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/10 17:53:02 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_general	g_gen;

int	_redirector_builtins(t_command *cmd, int *fd)
{
	if (cmd->in == -1 || cmd->out == -1)
	{
		builtins_exit(&g_gen, 1);
		g_gen.f_open = true;
		return (ms_errors("open", "no such file or directory !"), 1);
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
	{
		dup2(fd[1], STDOUT_FILENO);
		close(cmd->out);
	}
}

void	exec_builtins_f(t_command *cmd)
{
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
}

void	exec_builtins(t_command *cmd, bool pipe)
{
	int	fd[2];

	if (cmd->data)
	{
		if (!pipe)
		{
			if (_redirector_builtins(cmd, fd))
			{
				restore_fd(fd, cmd);
				return ;
			}
		}
		exec_builtins_f(cmd);
		if (!pipe)
			restore_fd(fd, cmd);
	}
}
