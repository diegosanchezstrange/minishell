/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:29:43 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/22 16:18:12 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_envmatrix(void)
{
	char	**environ;
	int		i;
	t_list	**cpy;

	cpy = ft_calloc(1, sizeof(void *));
	environ = ft_calloc(ft_lstsize(*(g_env.env)) + 1, sizeof(char *));
	i = 0;
	if (!(*(g_env.env)))
	{
		free(environ);
		free(cpy);
		return (NULL);
	}
	*cpy = *(g_env.env);
	while (*cpy)
	{
		environ[i] = ft_strdup((*cpy)->content);
		i++;
		(*cpy) = (*cpy)->next;
	}
	environ[i] = NULL;
	free(cpy);
	return (environ);
}

char	*ft_strjoin_path(char *path, char *cmd)
{
	char	*sol;
	char	*tmp;

	tmp = ft_strjoin("/", cmd);
	sol = ft_strjoin(path, tmp);
	free(tmp);
	return (sol);
}

char	*ft_getpath(char *cmd)
{
	char	**path;
	char	*tmp;
	char	*command;
	int		i;

	tmp = ft_getenv("PATH");
	if (!tmp)
		return (NULL);
	path = ft_split(tmp, ':');
	free(tmp);
	i = 0;
	while (path[i])
	{
		command = ft_strjoin_path(path[i], cmd);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	ft_free_split(path);
	return (NULL);
}

char	**ft_return_cmd(t_ast *node, char *cmd)
{
	char	**sol;
	int		i;

	sol = ft_calloc(sizeof(char *), ft_astsize_r(node) + 2);
	sol[0] = cmd;
	i = 1;
	while (node)
	{
		sol[i] = node->data;
		i++;
		node = node->right;
	}
	sol[i] = NULL;
	return (sol);
}

void	ft_exec_command(t_ast *node)
{
	char	**cmd;
	char	*path;
	char	**environ;
	int		ret;

	ret = EXIT_FAILURE;
	environ = ft_envmatrix();
	cmd = ft_return_cmd(node->left, node->data);
	if (access(cmd[0], F_OK) == 0)
		path = cmd[0];
	else
		path = ft_getpath(cmd[0]);
	if (!path)
	{
		printf("%s: command not found\n", cmd[0]);
		ft_free_split(environ);
		ft_free_split(cmd);
		exit(127);
	}
	else
		execve(path, cmd, environ);
	perror("mini");
	ft_free_split(environ);
	ft_free_split(cmd);
	exit(ret);
}
