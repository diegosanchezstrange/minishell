/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:40:03 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/15 20:24:50 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	ll;

	if (little[0] == 0)
		return ((char *)big);
	i = 0;
	j = 0;
	ll = ft_strlen(little);
	while (big[i] && i < len)
	{
		while (i + j < len && little[j] && big[i + j] == little[j])
			j++;
		if (j == ll)
			return (((char *) big) + i);
		else
			j = 0;
		i++;
	}
	return (NULL);
}
