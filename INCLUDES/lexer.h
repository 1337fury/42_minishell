/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:19:38 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/30 18:21:36 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

typedef struct s_bit
{
	unsigned int is : 1;
} t_bit;

//  None of these are divisible by 2, 3, 5, 7
#define S_CMD 1
#define E_CMD 11
#define SPACE 13
#define SQUOTE 17
#define DQUOTE 19

// divisible by 5
#define PIPE 35
#define OR 55
#define AND 85

// divisible by 7
#define LEFT_PAR 49
#define RIGHT_PAR 77

#define BUILTIN 299
// #define BUILTIN 299

// divisible by 3
#define LESS 3
#define APPEND 9
#define GREAT 27
#define HERDOC 33

// divisible by 2
#define STR 2
#define VAR 4
#define WILD 8

typedef struct s_scanner
{
	int	start;
	int current;
} t_scanner;

typedef struct s_list
{
	int		size;
	t_node	*head;
	t_node	*tail;
}	t_list;

t_list	*fry_lexer(char *cmd);
t_list	*get_token(char *cmd);
bool	is_clean(t_list *list);
t_list	*create_list(void);
void	spaces_handler(t_list *lexer, int *current, char *cmd);
void	squote_handler(t_list *lexer, t_scanner *point, char *cmd);
void	dollar_handler(t_list *lexer, t_scanner *point, char *cmd);
void	dquote_handler(t_list *lexer, t_scanner *point, char *cmd);
void	par_handler(t_list *lexer, t_scanner *point, char *cmd);
void	operator_handler(t_list *lexer,  t_scanner *point, char *cmd);
void	default_handler(t_list *lexer, t_scanner *point, char *cmd);
char	*fry_char_to_str(char c);

#endif