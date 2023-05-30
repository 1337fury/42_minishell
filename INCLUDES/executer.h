/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:39:56 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/28 19:23:40 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
#define EXECUTER_H

#include "expander.h"

int		executer(t_table *table);
void	exec_family(t_family *family);
int		check_pipe(t_command *curr);
int		close_fds(t_command *cmd, t_family *fam);
int		setup_outin(t_command *cmd, int size);
int		_close_pipes(t_family *fam);
int		close_fds(t_command *cmd, t_family *fam);
int		dup_close(int oldf, int newf, bool is_last);
void	_execve(char *cmd, char **args);

#endif