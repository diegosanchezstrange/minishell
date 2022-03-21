/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:23:53 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/21 13:55:32 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isspace(int c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

void	ft_skip_spaces(t_pstatus *status)
{
	//while (status->data[status->curr] == ' ')
	while (ft_isspace(status->data[status->curr]))
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
