#include <minishell.h>

void	ft_export(t_ast *tree)
{
	t_list	**cpy;
	char	**data;

	cpy = ft_calloc(1, sizeof(void *));
	*cpy = g_env;
	if (!tree->left->data)
		return ;
	data = ft_split(tree->left->data, '=');
	while ((*cpy)->next)
	{
		if (ft_strnstr((*cpy)->next->content, data[0], ft_strlen(data[0])))
		{
			free((*cpy)->next->content);
			(*cpy)->next->content = ft_strdup(tree->left->data);
			return ;
		}
		(*cpy) = (*cpy)->next;
	}
	ft_free_split(data);
	free(cpy);
	ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(tree->left->data)));
}
