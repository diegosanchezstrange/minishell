/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:13:52 by mclerico          #+#    #+#             */
/*   Updated: 2022/02/15 21:08:39 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_split(char **s)
{
	char	**str;

	str = s;
    while (*str)
	{
		free(*str);
		str++;
	}
	free(s);
}

char	**ft_envmatrix()
{
	char	**environ;
	int		i;
	t_list	**cpy;

	cpy = ft_calloc(1, sizeof(void *));
	environ = ft_calloc(ft_lstsize(g_env) + 1, sizeof(char *));
	i = 0;
	if (!g_env)
	{
		free(environ);
		return NULL;
	}
	*cpy = g_env;
	while (*cpy)
	{
		environ[i++] = ft_strdup((*cpy)->content);
		(*cpy) = (*cpy)->next;
	}
	environ[i]= NULL;
	return (environ);
}

int	valid_builtins(t_ast *tree)
{
	t_ast 	*vars;

	vars = tree->left;
	if (ft_strncmp(tree->data, "echo", 4))
		return (1);
	if (ft_strncmp(tree->data ,"pwd", 3) && !vars)
		return (1);
	if (ft_strncmp(tree->data ,"export", 6))
		return (1);
	if (ft_strncmp(tree->data, "unset", 5) && vars != NULL)
		return (1);
	if ((ft_strncmp(tree->data, "env", 3) || ft_strncmp(tree->data, "exit", 4)) 
			&& !vars)
		return (1);
	else
		return (0);
}

