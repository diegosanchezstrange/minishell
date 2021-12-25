/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 13:14:11 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/16 16:35:14 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cs;
	size_t			i;

	i = 0;
	cs = (unsigned char *)s;
	while (i < n)
	{
		if (cs[i] == ((unsigned char)c))
			return (cs + i);
		i++;
	}
	return (NULL);
}
