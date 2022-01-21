#include <minishell.h>

void	ft_astadd_right(t_ast **tree, t_ast *new)
{
	if (!new || !tree)
		return ;
	if (!*tree)
		*tree = new;
	else
		(*tree)->right = new;
}
