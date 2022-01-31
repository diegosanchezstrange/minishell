#include <minishell.h>

t_ast	*ft_astget_last_r(t_ast *tree)
{
	if (!tree)
		return (NULL);
	while (tree->right)
	{
		tree = tree->right;
	}
	return (tree);
}