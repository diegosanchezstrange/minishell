/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:05:53 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/12 20:59:13 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;
	size_t	dlen;

	i = ft_strlen(dst);
	dlen = i;
	res = ft_strlen(src);
	if (size <= dlen)
		return (res + size);
	else
		res += dlen;
	j = 0;
	while (src[j] != '\0' && j + 1 < size - dlen)
	{
		dst[i] = src[j];
		i += 1;
		j += 1;
	}
	if (dlen + j < size)
		dst[i] = '\0';
	return (res);
}
