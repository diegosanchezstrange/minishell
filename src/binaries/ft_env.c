/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:37:33 by mclerico          #+#    #+#             */
/*   Updated: 2022/02/22 18:49:43 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(int fd)
{
	t_list	**cpy;

	cpy = ft_calloc(1, sizeof(void *));
	*cpy = *(g_env.env);
	while (*cpy)
	{
		write(fd, (char *)(*cpy)->content, ft_strlen((char *)(*cpy)->content));
		write(fd, "\n", 1);
		*cpy = (*cpy)->next;
	}
	free(cpy);
}
