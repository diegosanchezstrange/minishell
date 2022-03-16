/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_get_last_l.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:47:07 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/16 21:47:09 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast	*ft_astget_last_l(t_ast *tree)
{
	if (!tree)
		return (NULL);
	while (tree->left)
	{
		tree = tree->left;
	}
	return (tree);
}
