#include <minishell.h>

void	ft_astappend_r(t_ast **tree, t_ast *new)
{
	t_ast	*last;

	if (!tree || !new)
		return ;
	if (*tree == NULL)
		*tree = new;
	else
	{
		last = ft_astget_last_r(*tree);
		last->right = new;
	}
}