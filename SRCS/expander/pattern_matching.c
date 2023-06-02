/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/01 16:26:32 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if a string matches a pattern
bool    is_match(char *string, char *pattern)
{
    char    *star;
    char    *s_p;

    star = NULL;
    s_p = string;
    while (*string)
    {
        if ((*pattern == '?') || (*pattern == *string))
        {
            string++;
            pattern++;
            continue ;
        }
        if (*pattern == '*')
        {
            star = pattern++;
            s_p = string;
            continue ;
        }
        if (star)
        {
            pattern = star + 1;
            string = ++s_p;
            continue ;
        }
        return (false);
    }
    while (*pattern == '*')
        pattern++;
    return (!(*pattern));
}

// Handles wildcard matching for a given node
t_node    *wildcard_handler(t_node *node)
{
    DIR *folder;
    struct dirent   *curr_file;
    char    *matched_files;

    folder = opendir(".");
    matched_files = ft_strdup("");
    if (folder != NULL)
    {
         while ((curr_file = readdir(folder)) != NULL)
             if (is_match(curr_file->d_name, node->value))
                    matched_files = join_with_space(matched_files, curr_file->d_name);
    }
    closedir(folder);
    // free(node->value);
    node->value = matched_files;
    return (node->next);
}
