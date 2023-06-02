/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:44:54 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/02 19:00:09 by abdeel-o         ###   ########.fr       */
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
	char	*builtins;

	if (!data)
		return (false);
	builtins = "echo,cd,export,env,unset,pwd,exit,";
	if (ft_strnstr(builtins, data, ft_strlen(builtins)))
		return (true);
	return (false);
}
