/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/04 18:23:33 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_general	g_gen;

/**
 * Executes a command in a separate process using fork().
 * Closes file descriptors and sets up input/output
 * redirection based on the command and his position.
 * Invokes the _execve() function to execute the command.
 * Handles specific error conditions and exits the child process accordingly.
 * If the command is the tail of the family, closes the pipes.
 */
void	multi_commands(t_command *cmd, t_family *fam, int *pids)
{
	static int	i;

	pids[i] = fork();
	if (!pids[i++])
	{
		close_fds(cmd, fam);
		if (setup_outin(cmd, fam->size) != 4)
			exit(1);
		_execve(cmd);
		if (errno == ENOENT)
			exit(127);
		if (errno == EACCES || errno == ENOTDIR)
			exit(126);
		exit(EXIT_FAILURE);
	}
	if (cmd == fam->tail)
	{
		i = 0;
		_close_pipes(fam);
	}
}

/**
 * Executes the commands in a pipeline family by iterating over the commands.
 * Skips commands of type PIPE_CMD.
 * Invokes the multi_commands function to execute each command.
 * Returns EXIT_SUCCESS upon successful execution of all commands.
 */
int	exec_pipes_cmds(t_family *family, int *pids)
{
	t_command	*curr;

	curr = family->head;
	while (curr)
	{
		if (curr->type == PIPE_CMD)
		{
			curr = curr->next;
			continue ;
		}
		multi_commands(curr, family, pids);
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

/**
 * Executes the commands in a pipeline family by iterating over the commands.
 * Skips commands of type PIPE_CMD.
 * Invokes the multi_commands function to execute each command.
 * Returns EXIT_SUCCESS upon successful execution of all commands.
 */
int	single_outin(t_command *cmd)
{
	int	read;
	int	write;

	if (cmd->in == -1 || cmd->out == -1)
		return (ms_errors("open", "No such file or directory !"), 1);
	read = STDIN_FILENO;
	write = STDOUT_FILENO;
	if (cmd->in != 0)
		read = cmd->in;
	if (cmd->out != 1)
		write = cmd->out;
	if (!(!read))
		dup_close(read, 0, 0);
	if (write != 1)
		dup_close(write, 1, 0);
	return (EXIT_SUCCESS);
}

/**
 * Executes a single command in a separate process using fork().
 * Sets up output/input redirection for the command.
 * Invokes the _execve() function to execute the command.
 * Handles specific error conditions and exits the child process accordingly.
 */
void	single_command(t_command *cmd, int *pids)
{
	pids[0] = fork();
	if (!pids[0])
	{
		if (single_outin(cmd))
			exit(1);
		_execve(cmd);
		if (errno == ENOENT)
			exit(127);
		if (errno == EACCES || errno == ENOTDIR)
			exit(126);
		exit(EXIT_FAILURE);
	}
}

/*
 * Executes a family of commands,
   which can be either piped commands or a single command.
 * If the family is a set of piped commands,
   executes them using the `exec_pipes_cmds` function.
 * If the family is a single command,
   executes it using the `single_command` function.
 * Waits for the child processes to finish executing and updates the exit status.
 */
void	exec_family(t_family *family)
{
	t_command	*curr_cmd;
	int			inx_exit[2];
	int			*child_pid;
	int			sh_wait;

	if (!family || !family->head || family->already_seen)
		return ;
	child_pid = ft_calloc(family->size, sizeof(int));
	curr_cmd = family->head;
	sh_wait = true;
	if (check_pipe(curr_cmd))
		exec_pipes_cmds(family, child_pid);
	else if (check_builtin(*curr_cmd->data))
	{
		exec_builtins(curr_cmd, false);
		sh_wait = false;
	}
	else
		single_command(curr_cmd, child_pid);
	if (sh_wait)
	{
		g_gen.u_exec = true;
		inx_exit[0] = -1;
		while (++inx_exit[0] < family->size)
			waitpid(child_pid[inx_exit[0]], &inx_exit[1], 0);
		g_gen.e_status = WEXITSTATUS(inx_exit[1]);
		g_gen.u_exec = false;
	}
}
