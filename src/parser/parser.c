#include <minishell.h>

t_token_type ft_get_token_type(char *token)
{
	if (!token)
		return (T_COMMAND);
	return (T_ARGUMENT);
}

t_list	**ft_parse_tokens(char **tokens)
{
	t_list	**token_list;
	t_token	*actual;

	token_list = ft_calloc(1, sizeof(t_list));
	if (!token_list)
		return (NULL);
	while (*tokens)
	{
		actual = ft_calloc(1, sizeof(t_token));
		if (!actual)
			return (NULL);
		actual->data = *tokens;
		actual->type = ft_get_token_type(*tokens);
		ft_lstadd_back(token_list, ft_lstnew(actual));
		tokens++;
	}
	return (token_list);
}
