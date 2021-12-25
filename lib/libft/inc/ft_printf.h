/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 19:40:48 by dsanchez          #+#    #+#             */
/*   Updated: 2021/10/26 21:18:29 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(char c);
int	ft_putstr(char *c);
int	ft_putnbr(int nbr);
int	ft_putnbr_u(unsigned int nbr);
int	ft_putnbr_p(void *add);
int	ft_putnbr_x(int n);
int	ft_putnbr_big_x(int n);
int	ft_printf(const char *format, ...);

#endif
