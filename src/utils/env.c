/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:10:50 by mclerico          #+#    #+#             */
/*   Updated: 2022/04/01 12:41:34 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_max(size_t s1, size_t s2)
{
	if (s1 >= s2)
		return (s1);
	return (s2);
}

int	ft_llen(char *s1, char *s2)
{
	if (ft_strlen(s1) >= ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}

void	ft_set_env_split(t_list *cpy, char **name, char **content)
{
	char	**tmp;

	tmp = ft_split(cpy->content, '=');
	free(*name);
	if (!tmp[0])
		*name = NULL;
	else
		*name = ft_strdup(tmp[0]);
	free(*content);
	if (!tmp[1])
		*content = NULL;
	else
		*content = ft_strdup(tmp[1]);
	ft_free_split(tmp);
}

void	ft_cloneenv(char **environ)
{
	int		i;
	int		n;	
	char	*new;

	i = 0;
	n = 0;
	g_env.l_cod = 0;
	g_env.env = (t_list **)ft_calloc(sizeof(t_list *), 1);
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "SHLVL", 5) == 0)
		{
			n = ft_atoi(&(environ[i][6])) + 1;
			new = ft_itoa(n);
			ft_lstadd_back(g_env.env, ft_lstnew(ft_strjoin("SHLVL=", new)));
			free(new);
		}
		else
			ft_lstadd_back(g_env.env, ft_lstnew(ft_strdup(environ[i])));
		i++;
	}
	if (n == 0)
		ft_lstadd_back(g_env.env, ft_lstnew(ft_strdup("SHLVL=1")));
}

char	*ft_getenv(char *name)
{
	t_list	**cpy;
	size_t	len;
	char	*sol;
	char	*cname;

	cpy = ft_calloc(sizeof(void *), 1);
	*cpy = *(g_env.env);
	len = ft_strlen(name);
	cname = NULL;
	sol = NULL;
	while (*cpy)
	{
		ft_set_env_split(*cpy, &(cname), &(sol));
		if (!ft_strncmp(cname, name, ft_max(len, ft_strlen((*cpy)->content))))
		{
			free(cpy);
			free(cname);
			return (sol);
		}
		*cpy = (*cpy)->next;
	}
	free(cname);
	free(sol);
	free(cpy);
	return (NULL);
}
