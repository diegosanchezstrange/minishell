#include <minishell.h>

int	ft_llen(char *s1, char *s2)
{
	if (ft_strlen(s1) >= ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}

int	ft_sorted(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		if (env[i + 1])
		{
			if (ft_strncmp(env[i], env[i + 1], 
						ft_llen(env[i], env[i + 1])) > 0)
				return (0);
		}
		i++;
	}
	return (1); 
}
void	ft_printenv(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		write(fd, env[i], ft_strlen(env[i]));
		i++;
	}
}
void	ft_sortenv(int fd)
{
	char	**env;
	char	*aux;
	int		i;

	env = ft_envmatrix();
	i = 0;
	while (!ft_sorted(env))
	{
		if (env[i + 1] && ft_strncmp(env[i], env[i + 1],
						ft_llen(env[i], env[i + 1])) > 0)
		{
			aux = ft_strdup(env[i]);
			free(env[i]);
			env[i] = ft_strdup(env[i + 1]);
			free(env[i + 1]);
			env[i + 1] = ft_strdup(aux);
			free(aux);
		}
		if (!env[++i])
			i = 0;
	}
	ft_printenv(env, fd);
	ft_free_split(env);
}

void	ft_addvar(char **data, char *tree_data)
{
	t_list	**cpy;
	
	cpy = ft_calloc(1, sizeof(void *));
	*cpy = *(g_env.env);
	while ((*cpy)->next)
	{
		if (ft_strnstr((*cpy)->next->content, data[0], ft_strlen(data[0])))
		{
			free((*cpy)->next->content);
			(*cpy)->next->content = ft_strdup(tree_data);
			return ;
		}
		(*cpy) = (*cpy)->next;
	}
	free(cpy);
	ft_lstadd_back(g_env.env, ft_lstnew(ft_strdup(tree_data)));
}

void	ft_export(t_ast *tree, int fd)
{
	char	**data;
	t_ast	*node;

	if (!tree->left)
	{
		ft_sortenv(fd);
		return ;
	}
	data = ft_split(tree->left->data, '=');
	node = tree->left;
	while (node)
	{
		ft_addvar(data, node->data);
		node = node->right;
		if(node)
			data = ft_split(node->data, '=');
	}
	ft_free_split(data);
}
