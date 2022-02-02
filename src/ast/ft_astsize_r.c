#include <minishell.h>

int	ft_astsize_r(t_ast *node)
{
	int	sol;

	sol = 0;
	while (node)
	{
		sol++;
		node = node->right;
	}
	return (sol);
}
