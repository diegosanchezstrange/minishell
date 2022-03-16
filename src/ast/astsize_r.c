/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astsize_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:40:17 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/16 21:40:18 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_astsize_r(t_ast *node)
{
	int	sol;

	sol = 0;
	while (node)
	{
		sol++;
		node = node->right;
	}
	return (sol);
}
