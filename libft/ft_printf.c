/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:39:50 by lottavi           #+#    #+#             */
/*   Updated: 2023/11/10 10:36:34 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(unsigned int i, int base)
{
	char	*base_set;
	int		count;
	int		n;

	base_set = "0123456789abcdef";
	count = 0;
	n = i % base;
	if (i / base > 0)
		count += ft_putnbr(i / base, base);
	count += ft_putchar(base_set[n]);
	return (count);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putint(int i)
{
	int	count;

	count = 0;
	if (i < 0)
	{
		count += ft_putchar('-');
		i *= -1;
	}
	count += ft_putnbr(i, 10);
	return (count);
}

int	ft_printf(char *string, ...)
{
	int			count;
	va_list		args;
	int			i;

	i = 0;
	count = 0;
	va_start(args, string);
	while (string[i])
	{
		if (string[i] == '%')
		{
			i++;
			if (string[i] == 's')
				count += ft_putstr(va_arg(args, char *));
			if (string[i] == 'd')
				count += ft_putint(va_arg(args, int));
			if (string[i] == 'x')
				count += ft_putnbr(va_arg(args, unsigned int), 16);
		}
		else
			count += ft_putchar(string[i]);
		i++;
	}
	va_end(args);
	return (count);
}
