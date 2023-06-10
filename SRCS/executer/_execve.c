/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/10 17:03:43 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_general	g_gen;

/*
** This function searches for a command in the directories listed in the PATH
environment variable.
** It returns the full path of the command if found, or returns NULL if
the command is not found.
** If an error occurs, it prints an error message and returns NULL.
*/
char	*_pathchr(char *cmd)
{
	char	*path;
	char	**paths;
	char	*cmd_tmp;	

	if (!*cmd)
		return (NULL);
	path = get_env_value("PATH", g_gen.ev, false);
	if (!path)
		path = ft_strdup("");
	paths = ft_split(path, ':');
	cmd_tmp = ft_strjoin("/", cmd);
	while (*paths)
	{
		*paths = ft_strjoin(*paths, cmd_tmp);
		if (!access(*paths, F_OK))
			return (*paths);
		paths++;
	}
	return (ms_errors(cmd, NOT_F), NULL);
}

/*
** This function searches for an executable command in the system.
** If the command contains a slash ('/'), it checks if the file exists and
returns the command itself if found.
** If the command does not contain a slash, it searches for the command in the
directories listed in the PATH environment variable using the _pathchr()
function.
** If the command is found, it returns the full path of the command. If the
command is not found or an error occurs, it prints an error message and returns
NULL.
*/
char	*find_exec(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK))
			return (cmd);
		else if (access(cmd, F_OK) == -1)
			return (ms_errors(cmd, N_FILE), NULL);
	}
	else if (!ft_strchr(cmd, '/'))
		return (_pathchr(cmd));
	return (NULL);
}

void	repair(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (!ft_strcmp(data[i], "\x02"))
			data[i] = ft_strdup("");
		i++;
	}
}

/*
** This function executes a command with the given arguments using the execve
system call.
** It first calls the find_exec() function to locate the full path of the
command.
** If the command is found, it attempts to execute it using execve and passes
the command arguments and environment variables.
** If the command is not found or an error occurs during execution, it prints
an error message.
*/
void	_execve(t_command *cmd)
{
	char	*cmd_e;
	char	**result;

	init_sig_handler_child();
	if (check_builtin(cmd->data[0]))
	{
		exec_builtins(cmd, true);
		exit (g_gen.e_status);
	}
	else
	{
		result = convert_env(&g_gen);
		cmd_e = find_exec(cmd->data[0]);
		if (!cmd_e)
			exit (127);
		repair(cmd->data);
		execve(cmd_e, cmd->data, result);
		ms_errors(cmd_e, strerror(errno));
	}
}
