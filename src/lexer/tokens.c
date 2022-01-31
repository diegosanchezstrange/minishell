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

int	ft_validate_redirs(t_pstatus *status, int *start)
{
	if ((status->type == T_D_OUT_REDIR || status->type == T_D_IN_REDIR)
		&& ft_strchr("<>", status->data[status->curr]))
		return (2);
	if ((status->type == T_OUT_REDIR || status->type == T_D_OUT_REDIR)
		&& status->data[status->curr] == '<')
		return (2);
	if ((status->type == T_IN_REDIR || status->type == T_D_IN_REDIR)
		&& status->data[status->curr] == '>')
		return (2);
	if (status->data[status->curr] == '>' && status->type == T_ARGUMENT)
		status->type = T_OUT_REDIR;
	else if (status->data[status->curr] == '>' && status->type == T_OUT_REDIR)
		status->type = T_D_OUT_REDIR;
	if (status->data[status->curr] == '<' && status->type == T_ARGUMENT)
		status->type = T_IN_REDIR;
	else if (status->data[status->curr] == '<' && status->type == T_IN_REDIR)
		status->type = T_D_IN_REDIR;
	*start += 1;
	return (0);
}

int	ft_check_token_end(t_pstatus *status, int *start)
{
	if (status->data[status->curr] == ' ' && status->state == P_NEUTRAL
		&& *start != status->curr)
		return (1);
	if (ft_strchr("<>|", status->data[status->curr]) && *start != status->curr
		&& status->state == P_NEUTRAL)
		return (1);
	if (ft_strchr("<>", status->data[status->curr]))
		return (ft_validate_redirs(status, start));
	if (status->data[status->curr] == '|' && status->state == P_NEUTRAL && status->type == T_ARGUMENT)
	{
		status->curr++;
		status->type = T_PIPE;
		return (1);
	}
	else if (status->data[status->curr] == '|' && status->state == P_NEUTRAL && status->type != T_ARGUMENT)
		return (2);
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

t_token	*ft_get_current_token(t_pstatus *status, char **actual)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = status->type;
	token->data = *actual;
	ft_extend_vars(&token->data);
	ft_parse_quotes(&token->data);
	return (token);
}

char	*ft_get_token(t_pstatus **status)
{
	int		start;
	int		val;

	ft_skip_spaces(*status);
	if (!(*status)->data[(*status)->curr])
		return (NULL);
	(*status)->state = P_NEUTRAL;
	(*status)->type = T_ARGUMENT;
	start = (*status)->curr;
	while ((*status)->data[(*status)->curr])
	{
		if (start == (*status)->curr && (*status)->type != T_ARGUMENT)
		{
			ft_skip_spaces(*status);
			start = (*status)->curr;
		}
		val = ft_check_token_end(*status, &start);
		if (val == 1)
			break ;
		else if (val == 2)
		{
			printf("Error near '%c'\n", (*status)->data[(*status)->curr]);
			(*status)->error = 1;
			return (NULL);
		}
		(*status)->curr++;
	}
	if ((*status)->type != T_ARGUMENT && (*status)->curr == start)
	{
		printf("Error near '%c'\n", (*status)->data[(*status)->curr]);
		(*status)->error = 1;
		return (NULL);
	}
	return (ft_substr((*status)->data, start, (*status)->curr - start));
}

void	ft_free_list(t_list **s)
{
	t_list	**str;

	str = s;
	while (*str)
	{
		free(*str);
		*str = (*str)->next;
	}
	free(s);
}

t_list	**ft_get_tokens(t_pstatus *status)
{
	char	*actual;
	t_token	*new;
	t_list	**tokens;

	tokens = ft_calloc(1, sizeof(void *));
	if (!tokens)
		return (NULL);
	actual = ft_get_token(&status);
	while (actual != NULL)
	{
		new = ft_get_current_token(status, &actual);
		if (ft_strlen(new->data))
			ft_lstadd_back(tokens, ft_lstnew(new));
		else
		{
			free(new->data);
			free(new);
		}
		actual = ft_get_token(&status);
	}
	if (status->error)
	{
		ft_lstclear(tokens, free);
		return (NULL);
	}
	return (tokens);
}