#include <minishell.h>

void	ft_structure_tree(t_list *tokens, t_ast **tree)
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
			ft_astadd_left(tree, ft_astnew(T_COMMAND_NODE, NULL));
		}
		tokens = tokens->next;
	}
	if (!*tree)
		ft_astadd_left(tree, ft_astnew(T_COMMAND_NODE, NULL));
	else
	{
		if (!(*tree)->right)
			ft_astadd_right(tree, ft_astnew(T_COMMAND_NODE, NULL));
		*tree = head;
	}
}

t_list	*ft_fill_tree(t_list *tokens, t_ast **tree)
{
	t_list	*current;

	current = tokens;
	if ((*tree)->type == T_PIPE_NODE)
	{
		//printf("Filling PIPE : %s\n", ((t_token *)current->content)->data);
		current = ft_fill_tree(current, &((*tree)->left));
		current = ft_fill_tree(current, &((*tree)->right));
	}
	if ((*tree)->type == T_COMMAND_NODE)
	{
		//printf("Filling COMMAND : %s\n", ((t_token *)current->content)->data);
		return (ft_fill_simple_command(current, tree));
	}
	return (tokens);
}

t_ast	**ft_generate_ast(t_list **tokens)
{
	t_ast	**head;

	head = ft_calloc(1, sizeof(void *));
	if (!head)
		return (NULL);
	ft_structure_tree(*tokens, head);
	ft_fill_tree(*tokens, head);
	return (head);
}