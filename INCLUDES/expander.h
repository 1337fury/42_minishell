/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:46:59 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/05 12:24:37 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft.h"
# include "lexer.h"

# define CMD_ROW 600
//Great then 1000
# define AND_ROW 2000
# define OR_ROW 4000

# define PIPE_CMD 800
# define EXECUTED_CMD 1000

typedef struct s_command
{
	int					in;
	int					out;
	char				**data;
	int					type;
	int					pos;
	int					fds[2];
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct s_family
{
	int			already_seen;
	int			size;
	t_command	*head;
	t_command	*tail;
}	t_family;

typedef struct s_row
{
	int				type;
	t_family		*family;
	struct s_row	*prev;
	struct s_row	*next;
}	t_row;

typedef struct s_table
{
	t_row	*head;
	t_row	*tail;
}	t_table;

t_table		*fry_expander(t_list *lexer);
void		create_table(t_table **table);
void		remove_dquote(t_list *lexer);
void		remove_empty(t_list *lexer);
void		table_add_back(t_table **expander, t_row *new_row);
t_row		*build_command(t_node **node);
t_row		*create_row(int type);
t_family	*family_init(void);
t_command	*create_t_command(int type);
void		redirect_handler(t_node **curr, t_command *cmd);
t_node		*basic_expander(t_list *lexer, t_node *curr);
void		destroy_node(t_list *lexer, t_node *node);
t_node		*retrieve_node(t_node *curr, int direction);
char		*retrieve_env_var(char *target);
t_node		*wildcard_handler(t_node *node);
void		family_add_back(t_family **family, t_command *new_cmd);

#endif