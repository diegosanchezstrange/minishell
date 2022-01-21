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
	if (ft_strchr("<>|", status->data[status->curr]) && start != status->curr && status->state == P_NEUTRAL)
		return (1);
	if (ft_strchr("<>|", status->data[status->curr]) && status->state == P_NEUTRAL)
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

t_token	*ft_get_current_token(char *actual)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	if (!ft_strncmp(actual, "|", ft_strlen(actual)))
		token->type = T_PIPE;
	else if (!ft_strncmp(actual, "<", ft_strlen(actual)))
		token->type = T_IN_REDIR;
	else if (!ft_strncmp(actual, ">", ft_strlen(actual)))
		token->type = T_OUT_REDIR;
	else
		token->type = T_ARGUMENT;
	token->data = actual;
	ft_extend_vars(&token->data);
	ft_parse_quotes(&token->data);
	return (token);
}

t_list	**ft_get_tokens(t_pstatus *status)
{
	char	*actual;
	t_token	*new;
	t_list	**tokens;

	tokens = ft_calloc(1, sizeof(void *));
	if (!tokens)
		return (NULL);
	actual = ft_get_token(status);
	while (actual != NULL)
	{
		new = ft_get_current_token(actual);
		if (ft_strlen(new->data))
			ft_lstadd_back(tokens, ft_lstnew(new));
		else
		{
			free(new->data);
			free(new);
		}
		actual = ft_get_token(status);
	}
	return (tokens);
}