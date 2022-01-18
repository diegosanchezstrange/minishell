/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:14:39 by dsanchez          #+#    #+#             */
/*   Updated: 2022/01/14 19:42:31 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_token_end(t_pstatus *status, int start)
{
	if (status->data[status->curr] == ' ' && status->state == P_NEUTRAL)
		return (1);
	if (ft_strchr("<>", status->data[status->curr]) && start != status->curr)
		return (1);
	if (ft_strchr("<>", status->data[status->curr]))
	{
		status->curr++;
		return (1);
	}
	if (status->data[status->curr] == '\"' && status->state == P_NEUTRAL)
		status->state = P_D_QUOTE;
	else if (status->data[status->curr] == '\"' && status->state == P_D_QUOTE)
        status->state = P_NEUTRAL;
	if (status->data[status->curr] == '\'' && status->state == P_NEUTRAL)
		status->state = P_S_QUOTE;
	else if (status->data[status->curr] == '\'' && status->state == P_S_QUOTE)
        status->state = P_NEUTRAL;
	return (0);
}

char	*ft_get_token(t_pstatus *status)
{
	int		start;

	ft_skip_spaces(status);
	if (!status->data[status->curr])
		return (NULL);
	status->state = P_NEUTRAL;
	start = status->curr;
	while (status->data[status->curr])
	{
		if (ft_check_token_end(status, start))
			break ;
		status->curr++;
	}
	return (ft_substr(status->data, start, status->curr - start));
}

char	**ft_get_tokens(t_pstatus *status)
{
	char	*actual;
	char	**tokens;
	int		num;

	tokens = NULL;
	actual = ft_get_token(status);
	num = 0;
	while (actual != NULL)
	{
		num++;
		tokens = ft_resize_tokens(num, tokens);
		ft_extend_vars(&actual);
		ft_parse_quotes(&actual);
		tokens[num - 1] = actual;
		actual = ft_get_token(status);
	}
	return (tokens);
}
