/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:15:51 by mclerico          #+#    #+#             */
/*   Updated: 2022/02/02 20:54:00 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
void	ft_echo(t_ast *tree)
{
	int		nline;

	tree = tree->left;
	nline = 0;
	if (ft_strncmp((tree->data), "-n", ft_strlen(tree->data)) == 0)
	{
		nline = 1;
		tree = tree->right;
	}
	while (tree)
	{
		write(1, (tree->data), ft_strlen(tree->data));
		tree = tree->right;
		if (tree)
			write(1, " ", 1);
	}
	if (nline == 1)
		write(1, "\n", 1);
}
