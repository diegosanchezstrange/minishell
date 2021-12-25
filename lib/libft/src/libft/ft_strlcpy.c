/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:59:36 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/15 20:31:28 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_copy(char *src, char *dest, unsigned int size)
{
	unsigned int	i;
	char			*s;
	char			*d;

	s = src;
	d = dest;
	i = 0;
	while (i++ < size)
	{
		*d++ = *s++;
	}	
	return (d);
}

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	l;

	l = ft_strlen(src);
	if (l + 1 < size)
	{
		ft_copy(src, dest, l + 1);
	}
	else if (size != 0)
	{
		ft_copy(src, dest, size - 1);
		dest[size - 1] = 0;
	}
	return (l);
}
