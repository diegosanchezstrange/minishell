#include <minishell.h>

int	valid_variable(char  *data)
{
	int	i;
	t_list	*cpy;

	i = 0;
	cpy = g_env;
	while (g_env)
	{
		if (ft_strncmp(g_env->content, data, ft_strlen(data)))
			return (1);
		g_env = g_env->next;
	}
	g_env = cpy;
	return (0);
}

void	ft_unset(t_ast *tree)
{
	t_list	**cpy;
	t_list	*next;
	char	*data;

	cpy = ft_calloc(1, sizeof(void *));
	*cpy = g_env;
	next = NULL;
	if (!tree->left->data)
		return ;
	data = tree->left->data;
	if (!valid_variable(data))
		return ;
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
