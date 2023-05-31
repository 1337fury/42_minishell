/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/31 15:25:49 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	_redirector_builtins(t_command *cmd)
// {
// 	if (cmd->in == -1 || cmd->out == -1)
// 		return (ms_errors("open", "no such file or directorie !"), 1);
// 	dup2(cmd->in, STDIN_FILENO);
// 	dup2(cmd->out, STDOUT_FILENO);
// 	return (EXIT_SUCCESS);
// }

// int	exec_builtins(t_command *cmd)
// {
// 	_redirector_builtins(cmd, fds);
// 	if (!ft_strncmp(cmd->data, "echo", ft_strlen(cmd->data)))
// 		return (_echo(/**/, cmd->data), 1);
// 	if (!ft_strncmp(cmd->data, "cd", ft_strlen(cmd->data)))
// 		return (_change_dir(/**/, cmd->data), 1);
// 	if (!ft_strncmp(cmd->data, "export", ft_strlen(cmd->data)))
// 		return (_export(/**/, cmd->data), 1);
// 	if (!ft_strncmp(cmd->data, "env", ft_strlen(cmd->data)))
// 		return (_env(/**/, cmd->data), 1);
// 	if (!ft_strncmp(cmd->data, "unset", ft_strlen(cmd->data)))
// 		return (_unset(/**/, cmd->data), 1);
// 	if (!ft_strncmp(cmd->data, "pwd", ft_strlen(cmd->data)))
// 		return (_pwd(/**/, cmd->data), 1);
// 	if (!ft_strncmp(cmd->data, "exit", ft_strlen(cmd->data)))
// 		return (_exit_shell(/**/, cmd->data), 1);
// 	if (!ft_strncmp(cmd->data, "echo", ft_strlen(cmd->data)))
// 		return (echo(/**/, cmd->data), 1);
// 	else
// 		return (false);
// }
