/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:31:31 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/02 17:23:25 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_general	g_gen;

void	reprompt(void)
{
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_handler(int sigint)
{
	if (sigint == SIGINT)
	{
		//kill_children();
		reprompt();
	}
}

void	init_signal_handler(void)
{
	g_gen.sa.sa_flags = 0;
	g_gen.sa.sa_handler = ctrl_handler;
	sigaction(SIGINT, &g_gen.sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	kill_shell(void)
{
	free(g_gen.line);
	ft_malloc(0, NULL, FREE_ALL, NULL);
	ft_putstr_fd("exit\n", 1);
	exit(g_gen.e_status);
}
