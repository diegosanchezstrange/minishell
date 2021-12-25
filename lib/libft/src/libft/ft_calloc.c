/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:21:33 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/08 14:30:36 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)malloc(nmemb * size);
	if (!res)
		return (NULL);
	while (i < size * nmemb)
	{
		res[i] = 0;
		i++;
	}
	return ((void *)res);
}
