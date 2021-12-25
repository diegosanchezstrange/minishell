/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:40:49 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/15 20:29:20 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_size(int n)
{
	int	c;

	c = 0;
	if (n < 0)
		c++;
	else if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*res;

	res = malloc(str_size(n) + 1);
	if (!res)
		return (NULL);
	i = str_size(n);
	if (n < 0)
		res[0] = '-';
	else if (n == 0)
		res[0] = 48;
	res[i--] = 0;
	while (n != 0)
	{
		if ((n % 10) > 0)
			res[i--] = (n % 10) + 48;
		else
			res[i--] = ((n % 10) * -1) + 48;
		n = n / 10;
	}
	return (res);
}
