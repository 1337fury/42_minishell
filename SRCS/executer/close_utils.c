/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/27 13:09:25 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Sets up the file descriptors for input and output redirection of the current command.
 * Returns an array of two integers, where the first element is the input file descriptor
 * and the second element is the output file descriptor.
 * If the allocation fails, it returns NULL.
 */
int	*setup_redirection(t_command *cmd, int size)
{
	int	*fds;

	fds = ft_calloc(2, sizeof(int));	
	if (!fds)
		return (NULL);
	if (cmd->pos == 0)
	{
		fds[0] = STDIN_FILENO;
		fds[1] = cmd->next->fds[1];
	}
	else if (cmd->pos == size - 1)
	{
		fds[0] = cmd->prev->fds[0];
		fds[1] = STDOUT_FILENO;
	}
	else
	{
		fds[0] = cmd->prev->fds[0];
		fds[1] = cmd->next->fds[1];
	}
	return (fds);
}

/**
 * Closes the file descriptors associated with pipes in the command family,
 * except for the ones specified by the current command.
 * Returns EXIT_SUCCESS if all closures are successful.
 * Returns EXIT_FAILURE if any closure operation fails.
 */
int	close_fds(t_command *cmd, t_family *fam)
{
	int			*fds;
	t_command	*curr;

	fds = setup_redirection(cmd, fam->size);
	if (!fds)
		return (EXIT_FAILURE);
	curr = fam->head;
	while (curr)
	{
		if (curr->type == PIPE_CMD)
		{
			if (curr->fds[0] != fds[0])
				close(curr->fds[0]);
			if (curr->fds[1] != fds[1])
				close(curr->fds[1]);
		}
		curr = curr->next;
	}
	free(fds);
	return (EXIT_SUCCESS);
}

/**
 * Closes the pipe file descriptors associated with the commands in the family.
 * Returns EXIT_SUCCESS if all closures are successful.
 * Returns EXIT_FAILURE if any closure operation fails.
 */
int	_close_pipes(t_family *fam)
{
	t_command	*curr;

	curr = fam->head;
	while (curr)
	{
		if (curr->type == PIPE_CMD)
		{
			if (close(curr->fds[0]) == -1 || close(curr->fds[1]) == -1)
				return (EXIT_FAILURE);
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
