/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:18:33 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/29 11:31:16 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_general	g_gen = {.e_status = 0, .envp = NULL};

/*
Initializes an environment and copy env to en->env_vars variable
Also sets the lexer and expander pointers to NULL.
@param en The environment struct to initialize.
@param env An array of environment variable strings.
@param lexer A pointer to a linked list representing the lexer.
@param expander A pointer to a linked list representing the expander.
@return EXIT_SUCCESS if successful, or EXIT_FAILURE if memory allocation failed.
*/
int	fry_init_all(char **env, t_list **lexer, t_table **expander)
{
	int	size;

	size = -1;
	g_gen.envp = ft_calloc(1, sizeof(t_envp));
	if (!g_gen.envp)
		return (EXIT_FAILURE);
	while (env[++size])
		;
	g_gen.envp->env_vars = ft_calloc(size + 1, sizeof(char *));
	g_gen.envp->size = size;
	if (!g_gen.envp->env_vars)
		return (EXIT_FAILURE);
	size = -1;
	while (env[++size])
		g_gen.envp->env_vars[size] = ft_strdup(env[size]);
	g_gen.envp->env_vars[size] = NULL;
	*lexer = NULL;
	*expander = NULL;
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_list	*lexer;
	t_table	*expander;

	(void)ac;
	(void)av;
	(void)line;
	if (fry_init_all(envp, &lexer, &expander))
		exit(1);
	while (true)
	{
		line = readline(GREEN"fry@shell ~ :"WHITE);
		lexer = fry_lexer(line);
		expander = fry_expander(lexer);
		executer(expander);
	}
	

	t_node *curr;

	if (lexer)
	{
		curr = lexer->head;
		while (curr)
		{
			printf("type : %d\n", curr->type);
			printf("data : %s\n", curr->value);
			curr = curr->next;
		}
	}
	return (0);
}
// system("leaks -q minishell");