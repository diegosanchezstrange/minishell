/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:52:58 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/16 23:45:18 by dsanchez         ###   ########.fr       */
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
	if (!tmp[1])
		*name = NULL;
	else
		*name = ft_strdup(tmp[0]);
	free(*content);
	if (!tmp[0])
		*content = NULL;
	else
		*content = ft_strdup(tmp[1]);
	ft_free_split(tmp);
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
		//free(cname);
		*cpy = (*cpy)->next;
	}
	free(cpy);
	return (NULL);
}
