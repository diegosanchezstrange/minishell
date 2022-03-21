/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 20:42:02 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/20 21:12:39 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_throw_err(t_list **cpy)
{
	printf("Format error\n");
	free(cpy);
	return (0);
}

int	ft_check_tokens(t_list *tokens)
{
	t_list	**cpy;
	int		pipe;

	cpy = ft_calloc(sizeof(void *), 1);
	*cpy = tokens;
	if (((t_token *)tokens->content)->type == T_PIPE)
		return (ft_throw_err(cpy));
	while (*cpy)
	{
		if (((t_token *)(*cpy)->content)->type == T_PIPE && pipe == 1)
			return (ft_throw_err(cpy));
		if (((t_token *)(*cpy)->content)->type == T_PIPE)
			pipe = 1;
		else
			pipe = 0;
		*cpy = (*cpy)->next;
	}
	if (pipe == 1)
		return (ft_throw_err(cpy));
	free(cpy);
	return (1);
}
