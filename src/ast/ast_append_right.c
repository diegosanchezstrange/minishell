/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_append_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:38:58 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/16 21:39:31 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_astappend_r(t_ast **tree, t_ast *new)
{
	t_ast	*last;

	if (!tree || !new)
		return ;
	if (*tree == NULL)
		*tree = new;
	else
	{
		last = ft_astget_last_r(*tree);
		last->right = new;
	}
}
