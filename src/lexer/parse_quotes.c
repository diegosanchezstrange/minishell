/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:50:59 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/31 14:27:22 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lex_states	ft_change_state(t_lex_states state, t_lex_states newState)
{
	if (state == P_NEUTRAL)
		return (newState);
	else
		return (P_NEUTRAL);
}

t_lex_states	ft_join_token(char **token, t_lex_states act,
		t_lex_states n, int i)
{
	char	*aux;
	char	*new;

	aux = ft_substr(*token, 0, i);
	new = ft_strjoin(aux, (*token) + i + 1);
	free(aux);
	free(*token);
	*token = new;
	return (ft_change_state(act, n));
}

void	ft_parse_quotes(char **token)
{
	int				i;
	t_lex_states	state;

	i = 0;
	state = P_NEUTRAL;
	while ((*token)[i])
	{
		if ((*token)[i] == '\"' && (state == P_NEUTRAL || state == P_D_QUOTE))
			state = ft_join_token(token, state, P_D_QUOTE, i);
		else if ((*token)[i] == '\''
				&& (state == P_NEUTRAL || state == P_S_QUOTE))
			state = ft_join_token(token, state, P_S_QUOTE, i);
		else
			i++;
	}
}
