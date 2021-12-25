/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 19:09:42 by dsanchez          #+#    #+#             */
/*   Updated: 2021/10/26 21:17:59 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	conversion_format(const char *format, va_list a_list)
{
	int	i;

	if (*format == 'c')
		i = ft_putchar(va_arg(a_list, int));
	else if (*format == 's')
		i = ft_putstr(va_arg(a_list, char *));
	else if (*format == 'd' || *format == 'i')
		i = ft_putnbr(va_arg(a_list, int));
	else if (*format == 'u')
		i = ft_putnbr_u(va_arg(a_list, int));
	else if (*format == 'p')
		i = ft_putnbr_p(va_arg(a_list, void *));
	else if (*format == 'x')
		i = ft_putnbr_x(va_arg(a_list, int));
	else if (*format == 'X')
		i = ft_putnbr_big_x(va_arg(a_list, int));
	else if (*format == '%')
		i = write(1, "%", 1);
	else
		i = 0;
	return (i);
}

int	num_len(int n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

int	ft_printf(const char *format, ...)
{
	va_list	a_list;
	int		i;
	int		c;
	int		l;

	va_start(a_list, format);
	i = 0;
	c = 0;
	l = ft_strlen(format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			c += conversion_format(&format[i + 1], a_list);
			i++;
		}
		else
			c += write(1, &format[i], 1);
		if (l == i)
			break ;
		i++;
	}
	va_end(a_list);
	return (c);
}
