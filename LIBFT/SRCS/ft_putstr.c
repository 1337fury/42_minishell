/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:39:39 by abdeel-o          #+#    #+#             */
/*   Updated: 2022/10/19 17:47:58 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	i;
	int	counter;

	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	i = 0;
	counter = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
		counter++;
	}
	return (counter);
}
