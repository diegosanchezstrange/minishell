/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:51:57 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/19 15:17:22 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_dupschild(int fd[], t_l_fd *r_fd)
{
	sig_ignore();
	close(fd[WRITE_END]); 
	if (r_fd)
		r_fd->fd[READ_END] = fd[READ_END];
	else
		close(fd[READ_END]);
}

t_l_fd	*ft_exec_tree(t_ast *tree, int pip, int *l_pid, t_l_fd *l_fd)
{
	int		fd[2];
	t_l_fd	*r_fd;

	r_fd = NULL;
	if (tree->type == T_PIPE_NODE)
	{
		r_fd = ft_exec_tree(tree->left, 1, l_pid, l_fd);
		ft_exec_tree(tree->right, 2, l_pid, r_fd);
		g_env.l_read = r_fd->fd[READ_END];
		free(r_fd);
	}
	else if (tree->type == T_COMMAND_NODE)
	{
		pipe(fd);
		if (pip == 1)
			r_fd = ft_calloc(sizeof(void *), 1);
		if (!tree->data)
			*l_pid = ft_exec_cmd(tree, l_fd, r_fd, fd);
		else if (ft_strnstr("envpwdechoexitunsetexportcd", tree->data, 27)
			&& valid_builtins(tree) == 1 && pip == 0)
			ft_exec_builtin(tree);
		else
			*l_pid = ft_exec_cmd(tree, l_fd, r_fd, fd);
		return (r_fd);
	}
	return (NULL);
}
