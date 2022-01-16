/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:23:53 by dsanchez          #+#    #+#             */
/*   Updated: 2022/01/14 18:24:25 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_skip_spaces(t_pstatus *status)
{
	while (status->data[status->curr] == ' ')
		status->curr++;
}

char	**ft_resize_tokens(int num, char **tokens)
{
	char	**new;
	int		i;

	new = ft_calloc(num + 1, sizeof(char *));
	if (!tokens)
		return (new);
	i = 0;
	while (tokens[i])
	{
		new[i] = tokens[i];
		i++;
	}
	new[i] = NULL;
	free(tokens);
	return (new);
}
