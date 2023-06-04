/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/04 11:22:43 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_general	g_gen;

char	**expand_heredoc(const char *line)
{
	int		s;
	int		e;
	int		h;
	char	**v_hold;

	h = 0;
	s = -1;
	v_hold = ft_calloc(128, sizeof(char *));
	while (line[++s])
	{
		e = 0;
		if (line[s] == '$')
		{
			s++;
			while (line[s + e] == '_' || ft_isalnum(line[s + e]))
				e++;
		}
		if (e > 0)
			v_hold[h++] = ft_substr(line, s, (e + s) - s);
	}
	return (v_hold);
}

void	*replace_word(char *line, char *word)
{
	char		*line_s;
	t_env		*var;
	int			i[3];
	int			size;

	ft_bzero(i, 3);
	var = get_env(word, g_gen.exp);
	size = ft_strlen(line);
	if (var)
		size += ft_strlen(var->value);
	line_s = ft_calloc(size + 1, 1);
	while (line[i[0]])
	{
		i[1] = 0;
		if (line[i[0]] == '$')
		{
			if (var)
				while (var->value[i[1]])
					line_s[i[2]++] = var->value[i[1]++];
			i[0] += ft_strlen(word) + 1;
		}
		else
			line_s[i[2]++] = line[i[0]++];
	}
	return (line_s);
}

char	*expand_variables(char	*line)
{
	char	**v_hold;
	char	*s_line;
	int		i;

	i = 0;
	v_hold = expand_heredoc(line);
	s_line = ft_strdup(line);
	// while (v_hold[i])
	// {
	// 	printf("STASH %d: %s\n", i, v_hold[i]);
	// 	i++;
	// }
	// i = 0;
	while (v_hold[i])
	{
		s_line = replace_word(s_line, v_hold[i]);
		i++;
	}
	return (line);
}

int    _expand(char *line, int fd)
{
	int i;
	char    *e_var;

	(void)fd;
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
		// if (ft_strchr(line, '$'))
		// 	line = expand_variables(line);
		// write(tab[1], line, ft_strlen(line));
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
