/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:51:22 by mclerico          #+#    #+#             */
/*   Updated: 2022/04/06 11:19:55 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_strcmp(char *s1, char *s2)
{
	int	n;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	n = ft_strlen(s1);
	while (n != 0)
	{
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 - *(unsigned char *)(s2 - 1));
		if (*s1++ == 0)
			break ;
		n--;
	}
	return (0);
}
void	ft_use_builtins(t_ast *tree, int fd)
{
	if (ft_strcmp(tree->data, "pwd") == 0)
		ft_pwd(fd);
	else if (ft_strcmp(tree->data, "echo") == 0)
		ft_echo(tree, fd);
	else if (ft_strcmp(tree->data, "exit") == 0)
		ft_exit();
	else if (ft_strcmp(tree->data, "env") == 0)
		ft_env(fd);
	else if (ft_strcmp(tree->data, "unset") == 0)
		ft_unset(tree);
	else if (ft_strcmp(tree->data, "export") == 0)
		ft_export(tree, fd);
	else if (ft_strcmp(tree->data, "cd") == 0)
		ft_cd(tree->left);
}

int	valid_builtins(t_ast *tree)
{
	t_ast	*vars;

	vars = tree->left;
	if (!ft_strcmp(tree->data, "echo"))
		return (1);
	if (!ft_strcmp(tree->data, "cd"))
		return (1);
	if (!ft_strcmp(tree->data, "pwd"))
		return (1);
	if (!ft_strcmp(tree->data, "export"))
		return (1);
	if (!ft_strcmp(tree->data, "unset"))
		return (1);
	if ((!ft_strcmp(tree->data, "env")
			|| !ft_strcmp(tree->data, "exit")) && !vars)
		return (1);
	else
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

int	ft_exec_cmd(t_ast *tree, t_l_fd *l_fd, t_l_fd *r_fd, int fd[])
{
	int		pid;

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
