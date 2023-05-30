/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:59:20 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/02/13 11:20:54 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_pformat(va_list arg, const char c);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n, int counter);
int	ft_putunsigned(unsigned int n, int counter);
int	ft_put_hexa(unsigned int number, char *base, int counter);
int	ft_putsign(void);
int	ft_putptr(void *ptr, char *base, int counter);

#endif
