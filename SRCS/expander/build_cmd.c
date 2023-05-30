/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/29 17:16:40 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for the beautiful(l3aks) NORMINETTE
void	_init(char **joined, t_command **cmd, int pos)
{
	(*joined) = "";
    (*cmd) = create_t_command(EXECUTED_CMD);
	(*cmd)->pos = pos;
}

// Creates a new command structure based on the current node and its subsequent nodes
t_command    *create_cmd(t_node **curr, int pos)
{
    char        *joined_data;
    t_command   *command;
	char		sep[2];

	sep[0] = '\x01';
	sep[1] = '\0';
   	_init(&joined_data, &command, pos);
    while (*curr && (!((*curr)->type % 2) || !((*curr)->type % 3)))
    {
        if (!((*curr)->type % 3))
		{
            redirect_handler(curr, command);
			(*curr) = (*curr)->next->next;
		}
        else if (!((*curr)->type % 2))
		{
            joined_data = ft_strjoin(joined_data, sep);
            joined_data = ft_strjoin(joined_data, (*curr)->value);
        	(*curr) = (*curr)->next;
		}
    }
    command->data = ft_split(joined_data, sep[0]);
    return (command);
}

// Builds a command row structure based on the current node and its subsequent nodes
t_row   *build_command(t_node **node)
{
    t_row       *cmd;
    t_family    *family;
	int			position;

    cmd = create_row(CMD_ROW);
    family = family_init();
	position = 0;
    while (*node && (!((*node)->type % 3) || !((*node)->type % 2) || (*node)->type == PIPE))
    {
        if (!((*node)->type % 2) || !((*node)->type % 3))
            family_add_back(&family, create_cmd(node, position++));
        else if ((*node)->type == PIPE)
        {
            family_add_back(&family, create_t_command(PIPE_CMD));
			family->size--;
            (*node) = (*node)->next;
        }
        else
            (*node) = (*node)->next;
    }
	cmd->family = family;
    return (cmd);
}
