/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:51:22 by mclerico          #+#    #+#             */
/*   Updated: 2022/04/01 12:47:16 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_use_builtins(t_ast *tree, int fd)
{
	if (ft_strncmp(tree->data, "pwd", 3) == 0)
		ft_pwd(fd);
	else if (ft_strncmp(tree->data, "echo", 4) == 0)
		ft_echo(tree, fd);
	else if (ft_strncmp(tree->data, "exit", 4) == 0)
		ft_exit(tree->left);
	else if (ft_strncmp(tree->data, "env", 3) == 0)
		ft_env(fd);
	else if (ft_strncmp(tree->data, "unset", 5) == 0)
		ft_unset(tree);
	else if (ft_strncmp(tree->data, "export", 5) == 0)
		ft_export(tree, fd);
	else if (ft_strncmp(tree->data, "cd", 2) == 0)
		ft_cd(tree->left);
	if (fd > 2)
		close(fd);
}

int	valid_builtins(t_ast *tree)
{
	t_ast	*vars;

	vars = tree->left;
	if (!ft_strncmp(tree->data, "echo", 4))
		return (1);
	if (!ft_strncmp(tree->data, "cd", 2))
		return (1);
	if (!ft_strncmp(tree->data, "pwd", 3))
		return (1);
	if (!ft_strncmp(tree->data, "export", 6))
		return (1);
	if (!ft_strncmp(tree->data, "unset", 5))
		return (1);
	if (!ft_strncmp(tree->data, "env", 3) && !vars)
		return (1);
	if (!ft_strncmp(tree->data, "exit", 4))
		return (1);
	return (0);
}

void	ft_exec_builtin(t_ast *tree)
{
	int	fdesc;
	int	in_fd;

	fdesc = 1;
	in_fd = ft_getredir(tree->right->left, 1);
	if (in_fd == -1)
	{
		g_env.l_cod = 1;
		return ;
	}
	if (in_fd > 2)
		close(in_fd);
	fdesc = ft_getredir(tree->right->right, 0);
	if (fdesc == -1)
	{
		g_env.l_cod = 1;
		return ;
	}
	if (!fdesc)
		fdesc = 1;
	ft_use_builtins(tree, fdesc);
}

int	ft_exec_cmd(t_ast *tree, t_l_fd *l_fd, t_l_fd *r_fd)
{
	int		pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_dups(l_fd, fd, r_fd, tree);
		if (!tree->data)
			exit(1);
		else if (ft_strnstr("envpwdechoexitunsetexportcd", tree->data, 27)
			&& valid_builtins(tree) == 1)
		{
			ft_use_builtins(tree, 1);
			exit(0);
		}
		ft_exec_command(tree);
	}
	else
	{
		if (l_fd)
			close(l_fd->fd[READ_END]);
		ft_dupschild(fd, r_fd);
	}
	return (pid);
}
