
#include <minishell.h>

void	ft_skip_spaces(t_pstatus *state)
{
	while (state->data[state->curr] == ' ')
	{
		state->curr++;
	}
}

int	ft_check_token_end(t_pstatus *status, int *start)
{
	if (status->data[status->curr] == ' ' && status->state == P_NEUTRAL)
		return (1);
	if (status->data[status->curr] == '\"' && status->state == P_NEUTRAL)
	{
		*start = status->curr + 1;
		status->state = P_D_QUOTE;
	}
	else if (status->data[status->curr] == '\"' && status->state == P_D_QUOTE)
		return (1);
	return (0);
}

char	*ft_get_token(t_pstatus *status)
{
	int		start;

	ft_skip_spaces(status);
	if (status->data[status->curr] == '\"' && status->state == P_D_QUOTE)
		status->curr++;
	if (!status->data[status->curr])
		return (NULL);
	status->state = P_NEUTRAL;
	start = status->curr;
	while (status->data[status->curr])
	{
		if (ft_check_token_end(status, &start))
			break ;
		status->curr++;
	}
	return (ft_substr(status->data, start, status->curr - start));
}

/*char	**ft_get_tokens(char *line)
{
	char	**tokens;

	tokens = ft_split(line,  ' ');
	return (tokens);
}*/

char	**ft_list_to_arr(t_list *list)
{
	char	**res;
	t_list	*actual;
	int		size;
	int		i;

	size = ft_lstsize(list);
	actual = list;
	res = (char **) ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (actual != NULL)
	{
		res[i] = (char *)actual->content;
		actual = actual->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_get_tokens(char *line)
{
	t_pstatus	status;
	char		*actual;
	t_list		**tokens;

	status.data = line;
	status.curr = 0;
	tokens = ft_calloc(1, sizeof(void *));
	actual = ft_get_token(&status);
	while (actual != NULL)
	{
		ft_lstadd_back(tokens, ft_lstnew(actual));
		actual = ft_get_token(&status);
	}
	return (ft_list_to_arr(*tokens));
}

