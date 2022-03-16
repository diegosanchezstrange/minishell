/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:38:23 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/16 21:38:24 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_astadd_left(t_ast **tree, t_ast *new)
{
	if (!new || !tree)
		return ;
	if (!*tree)
		*tree = new;
	else
		(*tree)->left = new;
}
