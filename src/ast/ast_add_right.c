/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:38:31 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/16 21:38:36 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_astadd_right(t_ast **tree, t_ast *new)
{
	if (!new || !tree)
		return ;
	if (!*tree)
		*tree = new;
	else
		(*tree)->right = new;
}
