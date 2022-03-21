/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:38:26 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/21 02:25:11 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		return (2);
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
	if (ft_strchr("<>", status->data[status->curr])
		&& status->state == P_NEUTRAL)
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
