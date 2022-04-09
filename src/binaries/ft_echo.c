/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:03:45 by mclerico          #+#    #+#             */
/*   Updated: 2022/04/06 10:15:06 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(t_ast *tree, int fd)
{
	int		nline;

	tree = tree->left;
	nline = 1;
	if (!tree)
	{
		write(fd, "\n", 1);
		return ;
	}
	if (ft_strncmp((tree->data), "-n", ft_strlen(tree->data)) == 0)
	{
		tree = tree-> right;
		if (!tree)
			return ;
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
