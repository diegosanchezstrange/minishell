/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:39:00 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/15 20:30:51 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	reslen(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	while (s1[i] && isset(s1[i], set))
		i++;
	while (j < len && isset(s1[len - j - 1], set))
		j++;
	return (len - (j + i));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		len;
	char	*res;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	start = 0;
	len = reslen(s1, set);
	if (len < 0)
		len = 0;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	while (s1[start] && isset(s1[start], set))
		start++;
	while (i < len)
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}
