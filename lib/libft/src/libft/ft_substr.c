/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:43:01 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/13 16:24:14 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	size;
	size_t	i;

	i = 0;
	size = len;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		size = 0;
	else if (ft_strlen(s) < len)
		size = ft_strlen(s) - start;
	substr = (char *)malloc((size + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (s[i + start] && i < size)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = 0;
	return (substr);
}
