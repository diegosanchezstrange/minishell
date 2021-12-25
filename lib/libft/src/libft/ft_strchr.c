/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 21:06:00 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/11 23:13:22 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*cs;

	cs = (char *)s;
	while (*cs)
	{
		if (*cs == (char)c)
			return (cs);
		cs++;
	}
	if (*cs == (char)c)
		return (cs);
	return (NULL);
}
