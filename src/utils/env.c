#include <minishell.h>

size_t	ft_max(size_t s1, size_t s2)
{
	if (s1 >= s2)
		return (s1);
	return (s2);
}

char	*ft_getenv(char *name)
{
	t_list	**cpy;
	size_t	len;
	char	*sol;
	char	**tmp;

	cpy = ft_calloc(sizeof(void *), 1);
	*cpy = *(g_env.env);
	len = ft_strlen(name);
	while (*cpy)
	{
		tmp = ft_split((*cpy)->content, '=');
		if (!tmp[1])
			sol = NULL;
		else 
			sol = ft_strdup(tmp[1]);
		if (!ft_strncmp(tmp[0], name, ft_max(len, ft_strlen((*cpy)->content))))
		{
			free(cpy);
			ft_free_split(tmp);
			return (sol);
		}
		ft_free_split(tmp);
		free(sol);
		*cpy = (*cpy)->next;
	}
	free(cpy);
	return (NULL);
}
