#include <minishell.h>

void	ft_removevar(char *data)
{
	t_list	**cpy;
	t_list	*next;

	cpy = ft_calloc(1, sizeof(void *));
	*cpy = *(g_env.env);
	next = NULL;
	while ((*cpy)->next)
	{
		if (ft_strnstr((*cpy)->next->content, data, ft_strlen(data)))
		{
			next = (*cpy)->next->next;
			ft_lstdelone((*cpy)->next, free);
			(*cpy)->next = next;
			return ;
		}
		(*cpy) = (*cpy)->next;
	}
	free(cpy);
	free(next);
}

void	ft_unset(t_ast *tree)
{
	char	*data;
	t_ast	*node;

	if (!tree->left)
		return ;
	data = tree->left->data;
	node = tree->left;
	while (node)
	{
		ft_removevar(data);
		node = node->right;
		if (node)
			data = node->data;
	}
}
