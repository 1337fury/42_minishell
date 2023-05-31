/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:18:33 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/31 19:32:01 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


extern t_general	g_gen;

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
	g_gen.ev = create_env(env);
	g_gen.exp = create_env(env);
	g_gen.e_status = 0;
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
	return (0);
}
// system("leaks -q minishell");