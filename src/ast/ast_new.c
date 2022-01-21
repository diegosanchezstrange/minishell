#include <minishell.h>

t_ast	*ft_astnew(t_node_type type, char *content)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->data = content;
	new->type = type;
	new->right = NULL;
	new->left = NULL;
	return (new);
}
