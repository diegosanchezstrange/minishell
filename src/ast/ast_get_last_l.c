#include <minishell.h>

t_ast	*ft_astget_last_l(t_ast *tree)
{
	if (!tree)
		return (NULL);
	while (tree->left)
	{
		tree = tree->left;
	}
	return (tree);
}