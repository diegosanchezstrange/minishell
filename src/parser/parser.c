#include <minishell.h>

void	ft_fill_with_pipes(t_list *tokens, t_ast **tree)
{
	*tree = NULL;
	while (tokens)
	{
		/*if (((t_token *) tokens->content)->type == T_PIPE)
		{

		}*/
		tokens = tokens->next;
	}
}

t_ast	**ft_generate_ast(t_list **tokens)
{
	t_ast	**head;

	head = ft_calloc(1, sizeof(void *));
	if (!head)
		return (NULL);
	ft_fill_with_pipes(*tokens, head);
	return (head);
}