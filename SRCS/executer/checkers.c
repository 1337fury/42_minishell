/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/02 17:43:23 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if there is a pipe command (|) in the command sequence starting from the current command (curr).
 * Returns true if a pipe command is found, and false otherwise.
*/
int	check_pipe(t_command *curr)
{
	while (curr != NULL)
	{
		if (curr->type == PIPE_CMD)
			return (true);
		curr = curr->next;
	}
	return (false);
}

/**
 * checks if a given command is a built-in command.
 * returns true if the command is a built-in command, and false otherwise.
 */
bool	check_builtin(char *data)
{
	int			i;
	static char	*builtins[15] = {"echo", "cd", "export",
		"env", "unset", "pwd", "exit", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(builtins[i], data))
			return (true);
		i++;
	}
	return (false);
}
