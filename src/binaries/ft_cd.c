/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:08:16 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/17 20:20:11 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_getact(char *var)
{
	t_list	**cpy;
	char	*path;

	cpy = ft_calloc(1, sizeof(void *));
	*cpy = *(g_env.env);
	while (*cpy)
	{
		if (ft_strnstr((*cpy)->content, var, ft_strlen(var)) != NULL)
			break ;
		*cpy = (*cpy)->next;
	}
	if (!*cpy)
		return ("");
	path = (*cpy)->content;
	path += ft_strlen(var);
	free(cpy);
	return (path);
}

char  *ft_joinwfree(char *s1, char *s2)
{
	char *act;
	char 	*new;

	act = s1;
	new = ft_strjoin(act, s2);
	free(act);
	return (new);
}

void	ft_update(char *var, char *path)
{
	t_list	**cpy;
	char	*new;

	cpy = ft_calloc(1, sizeof(void *));
	*cpy = *(g_env.env);
	new = ft_strjoin(var, "=");
	new = ft_joinwfree(new, path);
	while (*cpy)
	{
		if ((*cpy)->next
			&& ft_strnstr((*cpy)->next->content, var, ft_strlen(var)))
		{
			free((*cpy)->next->content);
			(*cpy)->next->content = ft_strdup(new);
			free(new);
			free(cpy);
			return ;
		}
		*cpy = (*cpy)->next;
	}
	if (!*cpy && ft_strnstr(var, "OLDPWD", 6) != NULL)
		ft_lstadd_back(g_env.env, ft_lstnew(ft_strdup(new)));
	free(cpy);
	free(new);
}

void	ft_home(void)
{
	char	*home;
	char	*act;

	home = ft_getact("HOME=");
	if (ft_strlen(home) == 0)
	{
		printf("cd: HOME not set\n");
		g_env.l_cod = 1;
		return ;
	}
	else
	{
		if (chdir(home) != -1)
		{
			act = ft_getact("PWD=");
			ft_update("OLDPWD", act);
			ft_update("PWD", home);
		}
		else
			perror(home);
	}
}

void	ft_cd(t_ast *path)
{
	char	*home;
	char	*old;

	if (!path)
		ft_home();
	else if (chdir(path->data) == -1)
	{
		perror(path->data);
		return ;
	}
	old = ft_getact("PWD");
	ft_update("OLDPWD", old);
	home = getcwd(0, 0);
	ft_update("PWD", home);
	free(home);
}
