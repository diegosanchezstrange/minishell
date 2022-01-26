#include <minishell.h>

t_lex_states	ft_change_state(t_lex_states state, t_lex_states newState)
{
	if (state == P_NEUTRAL)
		return (newState);
	else
		return (P_NEUTRAL);
}

void	ft_parse_quotes(char **token)
{
	int			i;
	char		*new;
	t_lex_states	state;

	i = 0;
	state = P_NEUTRAL;
	new = NULL;
	while ((*token)[i])
	{
		if ((*token)[i] == '\"' && (state == P_NEUTRAL || state == P_D_QUOTE))
		{
			new = ft_strjoin(ft_substr(*token, 0, i), (*token) + i + 1);
			free(*token);
			*token = new;
			state = ft_change_state(state, P_D_QUOTE);
		}
		else if ((*token)[i] == '\'' && (state == P_NEUTRAL || state == P_S_QUOTE))
		{
			new = ft_strjoin(ft_substr(*token, 0, i), (*token) + i + 1);
			free(*token);
			*token = new;
			state = ft_change_state(state, P_S_QUOTE);
		}
		else
			i++;
	}
}
