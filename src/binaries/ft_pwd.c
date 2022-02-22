/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:01:39 by mclerico          #+#    #+#             */
/*   Updated: 2022/02/22 18:59:54 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
void ft_pwd(void)
{
	t_list	**cpy;
	char *path;

	cpy = ft_calloc(1, sizeof(void *));
	*cpy = g_env;

	while (*cpy)
	{
		if (ft_strnstr((*cpy)->content, "PWD", 3) != NULL)
			break;
		*cpy = (*cpy)->next;
	}
	path = (*cpy)->content;
	path += 4;
	if (path)
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
	}
}
