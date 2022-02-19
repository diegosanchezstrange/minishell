/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:37:33 by mclerico          #+#    #+#             */
/*   Updated: 2022/02/02 20:55:22 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(void)
{
	t_list	**cpy;

	cpy = ft_calloc(1, sizeof(void *));
	*cpy = g_env;
	printf("START\n");
	while (*cpy)
	{
		printf("%s\n", (char *)(*cpy)->content);
		*cpy = (*cpy)->next;
	}
	free(cpy);
}
