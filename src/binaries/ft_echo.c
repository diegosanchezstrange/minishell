/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:15:51 by mclerico          #+#    #+#             */
/*   Updated: 2022/02/02 21:41:53 by dsanchez         ###   ########.fr       */ /*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(t_ast *tree, int fd)
{
	int		nline;

	tree = tree->left;
	nline = 0;
	if (!tree)
		return ;
	if (ft_strncmp((tree->data), "-n", ft_strlen(tree->data)) == 0)
	{
		tree = tree->right;
		if (tree)
			nline = 1;
	}
	while (tree)
	{
		write(fd, (tree->data), ft_strlen(tree->data));
		tree = tree->right;
		if (tree)
			write(fd, " ", 1);
	}
	if (nline == 1)
		write(fd, "\n", 1);
}
