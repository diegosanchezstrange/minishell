/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:51:57 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/16 21:18:14 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_getredir(t_ast *tree, int io)
{
	t_ast	**cpy;
	int		fd;

	fd = 0;
	if (!tree)
		return (0);
	cpy = ft_calloc(1, sizeof(void *));
	*cpy = tree;
	while (*cpy)
	{
		if ((*cpy)->type == T_OUT_NODE && io == 0)
			fd = open((*cpy)->data, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*cpy)->type == T_DOUBLE_OUT_NODE && io == 0)
			fd = open((*cpy)->data, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (((*cpy)->type == T_IN_NODE || (*cpy)->type == T_DOUBLE_IN_NODE)
			&& io == 1)
			fd = open((*cpy)->data, O_RDONLY ,0644);
		if (fd == -1)
			return (0);
		if (io == 0)
			(*cpy) = (*cpy)->right;
		else if (io == 1)
			(*cpy) = (*cpy)->left;
	}
	free(cpy);
	return (fd);
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
		free(r_fd);
	}
	else if (tree->type == T_COMMAND_NODE)
	{
		pipe(fd);
		if (pip == 1)
			r_fd = ft_calloc(sizeof(void *), 1);
		if (ft_strnstr("envpwdechoexitunsetexportcd", tree->data,
					27) != NULL && valid_builtins(tree) == 1 && pip == 0)
			ft_exec_builtin(tree, pip, r_fd, fd);
		else
			*l_pid = ft_exec_cmd(tree, l_fd, r_fd, fd); 
		return (r_fd);
	}
	return (NULL);
}
