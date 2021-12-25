/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:56:39 by dsanchez          #+#    #+#             */
/*   Updated: 2021/10/01 17:25:47 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nbr)
{
	unsigned int	n;
	int				c;

	c = 0;
	if (nbr < 0)
	{
		c += write(1, "-", 1);
		n = (unsigned int) nbr * -1;
	}
	else
		n = (unsigned int) nbr;
	if (n >= 10 )
	{
		c += ft_putnbr (n / 10);
		c += ft_putnbr (n % 10);
	}
	else
		c += ft_putchar(n + '0');
	return (c);
}

int	ft_putnbr_u(unsigned int nbr)
{
	int				c;

	c = 0;
	if (nbr >= 10 )
	{
		c += ft_putnbr (nbr / 10);
		c += ft_putnbr (nbr % 10);
	}
	else
		c += ft_putchar(nbr + '0');
	return (c);
}
