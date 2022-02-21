#include <minishell.h>
t_node_type	ft_map_types(t_token_type type)
{
	if (type == T_OUT_REDIR)
		return (T_OUT_NODE);
	else if (type == T_IN_REDIR)
		return (T_IN_NODE);
	else if (type == T_D_OUT_REDIR)
		return (T_DOUBLE_OUT_NODE);
	else if (type == T_D_IN_REDIR)
		return (T_DOUBLE_IN_NODE);
	return (0);
}

t_list	*ft_fill_simple_command(t_list *tokens, t_ast **tree)
{
	t_token	*actual;

	if (!*tree)
		return (tokens);
	ft_astadd_right(tree, ft_astnew(T_REDIR_NODE, NULL));
	actual = (t_token *)tokens->content;
	while (tokens && actual && actual->type != T_PIPE)
	{
		if (actual->type == T_ARGUMENT && (*tree)->data == NULL)
			(*tree)->data = actual->data;
		else if (actual->type == T_ARGUMENT && (*tree)->data != NULL)
			ft_astappend_r(&((*tree)->left),ft_astnew(T_ARGUMENT_NODE, actual->data));
		else if (actual->type == T_D_OUT_REDIR || actual->type == T_OUT_REDIR)
			ft_astappend_r(&((*tree)->right),ft_astnew(ft_map_types(actual->type), actual->data));
		else if (actual->type == T_D_IN_REDIR || actual->type == T_IN_REDIR)
			ft_astappend_l(&((*tree)->right),ft_astnew(ft_map_types(actual->type), actual->data));
		tokens = tokens->next;
		if (tokens)
			actual = ((t_token *)tokens->content);
	}
	if (actual->type == T_PIPE)
		tokens = tokens->next;
	return (tokens);
}
