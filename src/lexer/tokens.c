/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:14:39 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/22 14:47:53 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*ft_get_current_token(t_pstatus *status, char **actual)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = status->type;
	token->data = *actual;
	//ft_extend_vars(&token->data);
	//ft_parse_quotes(&token->data);
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
	if (c == 0)
		printf("Error near '\\n'\n");
	else
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
	if (((*status)->type != T_ARGUMENT && (*status)->curr == start)
			|| (*status)->state == P_D_QUOTE || (*status)->state == P_S_QUOTE)
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

	ft_extend_vars(&(status->data));
	printf("DATA : %s\n", status->data);
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
	if (status->error)
	{
		ft_lstclear(tokens, ft_free_token);
		free(tokens);
		free(actual);
		return (NULL);
	}
	return (tokens);
}
