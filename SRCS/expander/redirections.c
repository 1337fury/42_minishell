/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/03 20:14:42 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    _expand(char *line, int fd)
{
	int i;
	char    *e_var;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && (line[i] == '_' || ft_isalnum(line[i])))
		i++;
	if (i > 0)
		e_var = retrieve_env_var(ft_substr(line, 0, i));
	else
		e_var = ft_strdup("");
	while (*e_var)
		write(fd, &(*e_var++), 1);
	return (i);
}

void    _write(int fd, char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '$')
		{
			i++;
			i += _expand(line + i, fd);
		}
		if (line[i] == '$')
			continue ;
		write(fd, &line[i], 1);
		i++;
	}
}

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
		_write(tab[1], line);
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
