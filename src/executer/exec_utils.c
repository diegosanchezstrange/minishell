/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:13:52 by mclerico          #+#    #+#             */
/*   Updated: 2022/02/22 20:53:56 by mclerico         ###   ########.fr       */ /*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_envmatrix()
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
		return NULL;
	}
	*cpy = *(g_env.env);
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

char	*ft_strjoin_path(char *path, char *cmd)
{
	char	*sol;
	char	*tmp;

	tmp = ft_strjoin("/", cmd); sol = ft_strjoin(path, tmp);
	free(tmp);
	return (sol);
}

char	*ft_getpath(char **envp, char *cmd)
{
	char	**path;
	char	**tmp;
	char	*command;

	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		return ("");
	tmp = ft_split(*envp, '=');
	path = ft_split(tmp[1], ':');
	ft_free_split(tmp);
	tmp = path;
	while (*path)
	{
		command = ft_strjoin_path(*path, cmd);
		if (access(command, F_OK) == 0)
		{
			ft_free_split(tmp);
			return (command);
		}
		free(command);
		path++;
	}
	ft_free_split(tmp);
	return (NULL);
}

char	**ft_return_cmd(t_ast *node, char *cmd)
{
	char	**sol;
	int		i;

	sol = ft_calloc(sizeof(char *), ft_astsize_r(node) + 2);
	sol[0] = cmd; i = 1;
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

	if (!node)
		return ;
	ret = EXIT_FAILURE;
	environ = ft_envmatrix();
	cmd = ft_return_cmd(node->left, node->data);
	if (access(cmd[0], F_OK) == 0)
		path = cmd[0];
	else
		path = ft_getpath(environ, cmd[0]);
	if (!path)
	{
		ret = 127;
		execve(cmd[0], cmd, environ);
	}
	else
		execve(path, cmd, environ);
	perror(cmd[0]);
	ft_free_split(environ);
	ft_free_split(cmd);
	exit(ret);
}

int	ft_exec_cmd(t_ast *tree, t_l_fd *l_fd, t_l_fd *r_fd, int fd[])
{
	int		fdesc;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		sig_child();
		close(fd[READ_END]);
		if (l_fd)
		{
			dup2(l_fd->fd[READ_END], 0);
			close(l_fd->fd[READ_END]);
		}
		if (r_fd)
			dup2(fd[WRITE_END], 1);
		close(fd[WRITE_END]);
		fdesc = ft_getredir(tree->right->right, 0);
		if (fdesc == -1)
			exit(1);
		if (fdesc)
		{
			dup2(fdesc, 1);
			close(fdesc);
		}
		fdesc = ft_getredir(tree->right->left, 1);
		if (fdesc == -1)
			exit(1);
		if (fdesc)
		{
			dup2(fdesc, 0);
			close(fdesc);
		}
		if (!tree->data)
			exit(1);
		else if (ft_strnstr("envpwdechoexitunsetexportcd", tree->data,
					27) != NULL && valid_builtins(tree) == 1 )
		{
			ft_use_builtins(tree, 1);
			exit(0);
		}
		else
			ft_exec_command(tree);
	}
	else
	{
		sig_ignore();
		close(fd[WRITE_END]);
		if (r_fd)
			r_fd->fd[READ_END] = fd[READ_END];
		else
			close(fd[READ_END]);
	}
	return (pid);
}

