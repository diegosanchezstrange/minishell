/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:03:39 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/11 23:16:03 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;
	unsigned char	j;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	j = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
		if (csrc[i] == j)
		{
			cdest[i] = j;
			return (cdest + i + 1);
		}
	}
	return (NULL);
}
