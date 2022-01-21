#include <minishell.h>

void	ft_fill_with_pipes(t_list *tokens, t_ast **tree)
{
	t_token	*actual;
	t_ast	*head;

	head = NULL;
	while (tokens)
	{
		actual = ((t_token *) tokens->content);
		if (actual->type == T_PIPE)
		{
			ft_astadd_right(tree, ft_astnew(T_PIPE_NODE, actual->data));
			if (!head)
				head = *tree;
			if ((*tree)->right)
				*tree = (*tree)->right;
		}
		tokens = tokens->next;
	}
	*tree = head;
	printf("TREE : %s, %p\n", (*tree)->data, *tree);
}

void	ft_parse_simple_commands(t_list *tokens, t_ast **tree)
{
	t_list	*current;

	current = tokens;
	while (current)
	{
		current = current->next;
	}
}

t_ast	**ft_generate_ast(t_list **tokens)
{
	t_ast	**head;

	head = ft_calloc(1, sizeof(void *));
	if (!head)
		return (NULL);
	ft_fill_with_pipes(*tokens, head);
	ft_parse_simple_commands(*tokens, head);
	return (head);
}