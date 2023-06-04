/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:31:31 by hmeftah           #+#    #+#             */
/*   Updated: 2023/06/04 12:15:52 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_general	g_gen;

void	reprompt(void)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_handler(int sigint)
{
	if (sigint == SIGINT)
	{
		if (!g_gen.u_exec)
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

void	init_sig_handler_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

void	kill_shell(void)
{
	free(g_gen.line);
	ft_malloc(0, NULL, FREE_ALL, NULL);
	ft_putstr_fd("exit\n", 1);
	exit(g_gen.e_status);
}
