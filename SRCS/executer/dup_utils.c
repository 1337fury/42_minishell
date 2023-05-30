/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/27 13:07:24 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Duplicates the file descriptor `oldf` to `newf` using `dup2`.
 * If `is_last` is false, closes the `oldf` file descriptor.
 * Returns 2 if the duplication and closure operations are successful.
 * Otherwise, returns -1 and prints an error message.
 */
int	dup_close(int oldf, int newf, bool is_last)
{
	int	status;

	status = dup2(oldf, newf);
	if (status == -1)
	{
		ms_errors("dup2", "unable to duplicate");
		return (-1);
	}
	if (!is_last)
		status = close(oldf);
	if (status == -1)
	{
		ms_errors("close", "unable to close a file");
		return (-1);
	}
	return (2);
}

/**
 * Duplicates the input and output file descriptors for the first command in the pipeline.
 * If the command's input file descriptor is not 0 (stdin), duplicates the command's own input file descriptor to stdin.
 * If the command's output file descriptor is 1 (stdout), duplicates the output file descriptor from the next command's file descriptor array.
 * Otherwise, uses the command's own output file descriptor.
 * If the input file descriptor was duplicated, returns the result of the duplication and closure operation for the input file descriptor.
 * Otherwise, returns the result of the duplication and closure operation for the output file descriptor.
 */

int	_dup_first(t_command *cmd)
{
	int	read;
	int	write;
	int	status;

	status = 2;
	read = STDIN_FILENO;
	if (cmd->in != 0)
		read = cmd->in;
	if (cmd->out == 1)
		write = cmd->next->fds[1];
	else
		write = cmd->out;
	if (read != STDIN_FILENO)
		status = dup_close(read, STDIN_FILENO, 0);
	return (status * dup_close(write, STDOUT_FILENO, 0));
}

/**
 * Duplicates the input and output file descriptors for the last command in the pipeline.
 * If the command's input file descriptor is 0 (stdin), duplicates the input file descriptor from the previous command's file descriptor array.
 * If the command's output file descriptor is not 1 (stdout), duplicates the command's own output file descriptor.
 * Otherwise, uses the default stdout file descriptor.
 * Returns the result of the duplication and closure operations for both file descriptors.
 */
int	_dup_last(t_command *cmd)
{
	int	read;
	int	write;

	write = STDOUT_FILENO;
	if (cmd->in == 0)
		read = cmd->prev->fds[0];
	else
		read = cmd->in;
	if (cmd->out != 1)
		write = cmd->out;
	return (dup_close(read, 0, 1) * dup_close(write, 1, 1));
}

/**
 * Duplicates the input and output file descriptors for a command in the middle of the pipeline.
 * If the command's input file descriptor is 0 (stdin), duplicates the input file descriptor from the previous command's file descriptor array.
 * If the command's output file descriptor is 1 (stdout), duplicates the output file descriptor from the next command's file descriptor array.
 * Otherwise, duplicates the command's own input and output file descriptors.
 * Returns the result of the duplication and closure operations for both file descriptors.
 */
int	_dup_middle(t_command *cmd)
{
	int	read;
	int	write;

	if (cmd->in == 0)
		read = cmd->prev->fds[0];
	else
		read = cmd->in;
	if (cmd->out == 1)
		write = cmd->next->fds[1];
	else
		write = cmd->out;
	return (dup_close(read, 0, 0) * dup_close(write, 1, 0));
}

/**
 * Sets up input/output redirection for a command based on its file descriptors and position in the pipeline.
 * If the command's input or output file descriptor is invalid, returns -1 and displays an error message.
 * If the command is the first in the pipeline, duplicates the first file descriptor.
 * If the command is in the middle of the pipeline, duplicates both input and output file descriptors.
 * If the command is the last in the pipeline, duplicates the last file descriptor.
 * Returns EXIT_SUCCESS upon successful setup of input/output redirection.
 */
int	setup_outin(t_command *cmd, int size)
{
	if (cmd->in == -1 || cmd->out == -1)
		return (ms_errors("open", "no such file or directorie !"), -1);
	if (cmd->pos == 0)
		return (_dup_first(cmd));
	else if (cmd->pos != size - 1)
		return (_dup_middle(cmd));
	else
		return (_dup_last(cmd));
	return (EXIT_SUCCESS);
}
