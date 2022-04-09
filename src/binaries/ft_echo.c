/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:03:45 by mclerico          #+#    #+#             */
/*   Updated: 2022/04/09 15:35:59 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag[i++] != '-')
		return (0);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

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
	if (ft_is_flag(tree->data))
	{
		tree = tree->right;
		nline = 0;
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
