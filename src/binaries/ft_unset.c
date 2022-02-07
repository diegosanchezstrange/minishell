#include <minishell.h>

int	valid_variable(char  *data)
{
	int	i;
	t_list	*cpy;

	i = 0;
	cpy = env;
	while (env)
	{
		if (ft_strncmp(env->content, data, ft_strlen(data)))
			return (1);
		env = env->next;
	}
	env = cpy;
	return (0);
}

void	ft_unset(t_ast *tree)
{
	t_list	*cpy;
	char	*data;

	cpy = env;
	if (!tree->left->data)
		return ;
	data = tree->left->data;
	if (!valid_variable(data))
		return ;
	while (env)
	{
		if (ft_strncmp(env->content, data, ft_strlen(data)))
			ft_lstdelone(env, free);
		env = env->next;
	}
	env = cpy;
}
