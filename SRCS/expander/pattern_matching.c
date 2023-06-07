/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/07 11:56:10 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	start_check(char **string, char **pattern, char *star, char *s_p)
{
	while (**string)
    {
        if ((**pattern == '?') || (**pattern == **string))
        {
            (*string)++;
            (*pattern)++;
            continue ;
        }
        if (**pattern == '*')
        {
            star = (*pattern)++;
            s_p = (*string);
            continue ;
        }
		if (star)
        {
            *pattern = star + 1;
            *string = ++s_p;
            continue ;
        }
        return (false);
    }
	return (true);
}

bool    is_match(char *string, char *pattern)
{
	char    *star;
    char    *s_p;

    star = NULL;
    s_p = string;
    if (!start_check(&string, &pattern, star, s_p))
		return (false);
    while (*pattern == '*')
        pattern++;
    return (!(*pattern));
}

// Handles wildcard matching for a given node
t_node	*wildcard_handler(t_node *node)
{
	DIR				*folder;
	struct dirent	*curr_file;
	char			*matched_files;

	folder = opendir(".");
	matched_files = ft_strdup("");
	if (folder != NULL)
	{
		while (1)
		{
			curr_file = readdir(folder);
			if (!curr_file)
				break ;
			if (is_match(curr_file->d_name, node->value))
				matched_files = join_with_space(matched_files,
						curr_file->d_name);
		}
	}
	closedir(folder);
	node->value = ft_strtrim(matched_files, " ");
	return (node->next);
}
