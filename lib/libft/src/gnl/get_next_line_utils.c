/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:28:48 by dsanchez          #+#    #+#             */
/*   Updated: 2021/10/26 21:08:38 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != 0)
		len++;
	return (len);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;
	size_t			i;

	if (!dest && !src)
		return (dest);
	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	i = n;
	if (csrc <= cdest)
	{
		while (i--)
			cdest[i] = csrc[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			cdest[i] = csrc[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*res;
	int		s1_l;
	int		s2_l;
	int		s_l;

	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	s_l = s1_l + s2_l;
	if ((!s1 && !s2) || s_l == 0)
		return (NULL);
	res = (char *) malloc(s_l + 1);
	if (!res)
		return (NULL);
	ft_memmove(res, s1, s1_l);
	ft_memmove(res + s1_l, s2, s2_l);
	res[s_l] = 0;
	free(s1);
	return (res);
}
