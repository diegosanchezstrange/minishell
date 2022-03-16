/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_get_last_r.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:45:56 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/16 21:46:10 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast	*ft_astget_last_r(t_ast *tree)
{
	if (!tree)
		return (NULL);
	while (tree->right)
	{
		tree = tree->right;
	}
	return (tree);
}
