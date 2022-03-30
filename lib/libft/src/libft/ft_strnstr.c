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

static int	check_possible_needle(const char *p, const char *n, size_t s, int i)
{
	int		f_size;
	int		j;
	size_t	index;

	j = 0;
	index = i;
	f_size = 0;
	while (p[i] == n[j] && n[j] && p[i] && j + index < s)
	{
		f_size++;
		j++;
		i++;
	}
	return (f_size);
}

char	*ft_strnstr(const char	*str, const char *to_find, size_t len)
{
	size_t	i;
	int		size;

	if (to_find[0] == '\0')
		return ((char *)str);
	i = 0;
	size = (int) ft_strlen(to_find);
	while (str[i] && i < len)
	{
		if (str[i] == to_find[0])
		{
			if (check_possible_needle(str, to_find, len, i) == size)
				return ((char *)(str + i));
		}
		i++;
	}
	return (0);
}
