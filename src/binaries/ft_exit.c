/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:23:37 by mclerico          #+#    #+#             */
/*   Updated: 2022/04/01 12:32:36 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_aredigits(char *nmbr)
{
	int	i;

	i = 0;
	if (*nmbr == '-')
		i++;
	while (nmbr[i])
	{
		if (!ft_isdigit(nmbr[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_ast *node)
{
	unsigned char	num;

	if (!node)
		exit(0);
	if (!ft_aredigits(node->data))
		exit(0);
	num = ft_atoi(node->data);
	exit(num);
}
