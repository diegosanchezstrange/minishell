#include <minishell.h>

void	ft_astappend_l(t_ast **tree, t_ast *new)
{
	t_ast	*last;

	if (!tree || !new)
		return ;
	if (*tree == NULL)
		*tree = new;
	else
	{
		last = ft_astget_last_l(*tree);
		last->left = new;
	}
}