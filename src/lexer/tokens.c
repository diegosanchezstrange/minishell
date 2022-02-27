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

/*int	ft_validate_redirs(t_pstatus *status, int *start)
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
}*/

int	ft_istype_redir(t_token_type type)
{
	if (type == T_OUT_REDIR || type == T_IN_REDIR
		|| type == T_D_OUT_REDIR || type == T_D_IN_REDIR)
		return (1);
	else
		return (0);
}

int	ft_validate_redirs(t_pstatus *status, int *start)
{
	int	i;

	i = status->curr;
	if (ft_istype_redir(status->type) && status->curr == *start)
	{
		printf("TRAZA\n");
		return (2);
	}
	if (status->data[i] == '>' && status->type == T_ARGUMENT)
		status->type = T_OUT_REDIR;
	else if (status->data[i] == '<' && status->type == T_ARGUMENT)
		status->type = T_IN_REDIR;
	i++;
	if ((status->type == T_OUT_REDIR && status->data[i] == '<')
		|| (status->type == T_IN_REDIR && status->data[i] == '>'))
		return (2);
	if (status->data[i] == '>' && status->type == T_OUT_REDIR)
		status->type = T_D_OUT_REDIR;
	else if (status->data[i] == '<' && status->type == T_IN_REDIR)
		status->type = T_D_IN_REDIR;
	else
		i--;
	i++;
	while (status->data[i] == ' ')
		i++;
	status->curr = i - 1;
	*start = i;
	return (0);
}

void	ft_validate_quotes(t_pstatus *status)
{
	if (status->data[status->curr] == '\"' && status->state == P_NEUTRAL)
		status->state = P_D_QUOTE;
	else if (status->data[status->curr] == '\"' && status->state == P_D_QUOTE)
		status->state = P_NEUTRAL;
	if (status->data[status->curr] == '\'' && status->state == P_NEUTRAL)
		status->state = P_S_QUOTE;
	else if (status->data[status->curr] == '\'' && status->state == P_S_QUOTE)
		status->state = P_NEUTRAL;
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
	if (status->data[status->curr] == '|' && status->state == P_NEUTRAL
		&& status->type == T_ARGUMENT)
	{
		status->curr++;
		status->type = T_PIPE;
		return (1);
	}
	else if (status->data[status->curr] == '|' && status->state == P_NEUTRAL
		&& status->type != T_ARGUMENT)
		return (2);
	if (status->data[status->curr] == '\"'
		|| status->data[status->curr] == '\'')
		ft_validate_quotes(status);
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
	if (!ft_strlen(token->data))
	{
		free(token->data);
		free(token);
		return (NULL);
	}
	return (token);
}

char	*ft_error_near(t_pstatus **status, char c)
{
	printf("Error near '%c'\n", c);
	(*status)->error = 1;
	return (NULL);
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
		val = ft_check_token_end(*status, &start);
		if (val == 1)
			break ;
		else if (val == 2)
			return (ft_error_near(status, (*status)->data[(*status)->curr]));
		(*status)->curr++;
	}
	if ((*status)->type != T_ARGUMENT && (*status)->curr == start)
		return (ft_error_near(status, (*status)->data[(*status)->curr]));
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
		if (new)
			ft_lstadd_back(tokens, ft_lstnew(new));
		actual = ft_get_token(&status);
	}
	//if (new->type == T_PIPE)
	//	status->error = 1;
	if (status->error)
	{
		printf("TRAZA\n");
		ft_lstclear(tokens, free);
		return (NULL);
	}
	return (tokens);
}
