/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/29 11:05:25 by abdeel-o         ###   ########.fr       */
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
	while(true)
	{
		line = readline("herdoc> ");
		if (!ft_strncmp(line, eof, ft_strlen(eof)) || !line)
			break ;
		// expand herdoc vars later
		write(tab[1], line, ft_strlen(line));
		write(tab[1], "\n", 1);
	}
	close(tab[1]);
	return (tab[0]);
}
// Handles the redirection for a given command based on the type of redirection specified in the current node
void	redirect_handler(t_node **curr, t_command *cmd)
{
	char	*file_name;

	file_name = (*curr)->next->value;
	if ((*curr)->type == LESS)
		cmd->in = open(file_name, LESS_FLAG, 0644);
	else if ((*curr)->type == GREAT)
		cmd->out = open(file_name, GREAT_FLAG, 0644);
	else if ((*curr)->type == APPEND)
		cmd->out = open(file_name, APPEND_FLAG, 0644);
	else
		cmd->in = herdoc_handler((*curr)->next);
}
