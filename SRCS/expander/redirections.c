/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/02 16:18:44 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handles the heredoc functionality for a given node
// Returns: The file descriptor of the read end of the pipe
int	herdoc_handler(t_node *curr)
{
	int		tab[2];
	char	*line;
	char	*eof;

	if (pipe(tab) == -1)
		return (-1);
	line = NULL;
	eof = curr->value;
	while (true)
	{
		line = readline("herdoc> ");
		if (!line || !ft_strncmp(line, eof, ft_strlen(eof)))
			break ;
		// expand herdoc vars later
		write(tab[1], line, ft_strlen(line));
		write(tab[1], "\n", 1);
	}
	close(tab[1]);
	return (tab[0]);
}

/*Handles the redirection for a given command based on
the type of redirection specified in the current node*/
void	redirect_handler(t_node **curr, t_command *cmd)
{
	char	*file_name;

	file_name = (*curr)->next->value;
	if ((*curr)->type == LESS)
		cmd->in = open(file_name, O_RDONLY, 0644);
	else if ((*curr)->type == GREAT)
		cmd->out = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if ((*curr)->type == APPEND)
		cmd->out = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		cmd->in = herdoc_handler((*curr)->next);
}
