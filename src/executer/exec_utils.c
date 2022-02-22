/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:13:52 by mclerico          #+#    #+#             */
/*   Updated: 2022/02/22 20:53:56 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		environ[i] = ft_strdup((*cpy)->content);
		i++;
		(*cpy) = (*cpy)->next;
	}
	environ[i]= NULL;
	free(cpy);
	return (environ);
}

void	ft_use_builtins(t_ast *tree)
{
	if (ft_strncmp(tree->data, "pwd", 3) == 0)
	{
		ft_pwd(); printf("trazaaaaa\n");}
	else if (ft_strncmp(tree->data, "echo", 4) == 0)
		ft_echo(tree);
	else if (ft_strncmp(tree->data, "exit", 4) == 0)
		ft_exit();
	else if (ft_strncmp(tree->data, "env", 3) == 0)
		ft_env();
	else if (ft_strncmp(tree->data, "unset", 5) == 0)
		ft_unset(tree);
	else if (ft_strncmp(tree->data, "export", 5) == 0)
		ft_export(tree);
}

int	valid_builtins(t_ast *tree)
{
	t_ast	*vars;

	vars = tree->left;
	if (!ft_strncmp(tree->data, "echo", 4))
		return (1);
	if (!ft_strncmp(tree->data, "pwd", 3))
		return (1);
	if (!ft_strncmp(tree->data, "export", 6))
		return (1);
	if (!ft_strncmp(tree->data, "unset", 5) && vars != NULL)
		return (1);
	if ((!ft_strncmp(tree->data, "env", 3)
			|| !ft_strncmp(tree->data, "exit", 4)) && !vars)
		return (1);
	else
		return (0);
}
