/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:32:18 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/17 19:32:25 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_getact(void)
{
	t_list	**cpy;
	char	*path;

	cpy = ft_calloc(1, sizeof(void *));
	*cpy = *(g_env.env);
	while (*cpy)
	{
		if (ft_strnstr((*cpy)->content, "PWD", 3) != NULL)
			break ;
		*cpy = (*cpy)->next;
	}
	if (!*cpy)
		return ("");
	path = (*cpy)->content;
	path += 4;
	free(cpy);
	return (path);
}

void	ft_update(char *var, char *path)
{
	t_list	**cpy;
	char	*new;

	cpy = ft_calloc(1, sizeof(void *));
	*cpy = *(g_env.env);
	new = ft_strjoin(var, "=");
	new = ft_strjoin(new, path);
	while (*cpy)
	{
		if ((*cpy)->next
			&& ft_strnstr((*cpy)->next->content, var, ft_strlen(var)))
		{
			free((*cpy)->next->content);
			(*cpy)->next->content = ft_strdup(new);
			return ;
		}
		*cpy = (*cpy)->next;
	}
	if (!*cpy && ft_strnstr(var, "OLDPWD", 6) != NULL)
		ft_lstadd_back(g_env.env, ft_lstnew(ft_strdup(new)));
	free(cpy);
	free(new);
}

void	ft_cd(t_ast *path)
{
	char	*home;
	char	*old;

	if (chdir(path->data) == -1)
		return ;
	old = ft_getact();
	ft_update("OLDPWD", old);
	home = getcwd(0, 0);
	ft_update("PWD", home);
}
