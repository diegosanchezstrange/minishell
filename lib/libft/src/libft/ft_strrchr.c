/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 21:11:58 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/11 23:13:01 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*cs;
	char	*res;

	cs = (char *)s;
	res = NULL;
	while (*cs)
	{
		if (*cs == (char)c)
			res = cs;
		cs++;
	}
	if (*cs == (char)c)
		res = cs;
	return (res);
}
