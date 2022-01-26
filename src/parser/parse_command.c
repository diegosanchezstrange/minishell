#include <minishell.h>

t_list	*ft_fill_simple_command(t_list *tokens, t_ast **tree)
{
	t_token	*actual;
	int		pipe;

	pipe = 0;
	if (!*tree)
		return (tokens);
	while (tokens && !pipe)
	{
		actual = ((t_token *)tokens->content);
		if (actual->type == T_PIPE)
			pipe = 1;
		tokens = tokens->next;
	}
	return (tokens);
}
