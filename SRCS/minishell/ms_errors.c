/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:03:38 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/06/04 17:15:21 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_errors(char *part, char *usage)
{
	ft_putstr_fd(part, 2);
	ft_putstr_fd(" : ", 2);
	if (usage != NULL)
		ft_putstr_fd(usage, 2);
	write(2, "\n", 1);
}
