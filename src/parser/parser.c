
#include <minishell.h>

char	**ft_get_tokens(char *line)
{
	char	**tokens;

	tokens = ft_split(line,  ' ');
	return (tokens);
}

void	ft_skip_spaces(t_pstatus *state)
{
	while (state->data[state->curr] == ' ')
	{
		state->curr++;
	}
}

char	*ft_get_token(t_pstatus *status)
{
	int		start;

	ft_skip_spaces(status);
	status->state = P_NEUTRAL;
	start = status->curr;
	while (status->data[status->curr])
	{
		if (status->data[status->curr] == ' ' && status->state == P_NEUTRAL)
			break;
		if (status->data[status->curr] == '\"' && status->state == P_NEUTRAL)
		{
			start = status->curr + 1;
			status->state = P_D_QUOTE;
		}
		else if (status->data[status->curr] == '\"' && status->state == P_D_QUOTE)
			break;
		status->curr++;
	}
	return (ft_substr(status->data, start, status->curr - start));
}
