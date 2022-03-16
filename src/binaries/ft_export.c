/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:50:24 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/16 21:15:43 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_sorted(char **ev)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i + 1])
		{
			if (ft_strncmp(ev[i], ev[i + 1], ft_llen(ev[i], ev[i + 1])) > 0)
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
	char	**e;
	char	*aux;
	int		i;

	e = ft_envmatrix();
	i = 0;
	while (!ft_sorted(e))
	{
		if (e[i + 1]
			&& ft_strncmp(e[i], e[i + 1], ft_llen(e[i], e[i + 1])) > 0)
		{
			aux = ft_strdup(e[i]);
			free(e[i]);
			e[i] = ft_strdup(e[i + 1]);
			free(e[i + 1]);
			e[i + 1] = ft_strdup(aux);
			free(aux);
		}
		if (!e[++i])
			i = 0;
	}
	ft_printenv(e, fd);
	ft_free_split(e);
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
		if (node)
			data = ft_split(node->data, '=');
	}
	ft_free_split(data);
}
