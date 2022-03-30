/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:28:09 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/20 16:37:08 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_open_file(char *name, t_node_type type, int io, int old_fd)
{
	int	fd;

	fd = -1;
	if (old_fd != -1)
		close(fd);
	if (type == T_OUT_NODE && io == 0)
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (type == T_DOUBLE_OUT_NODE && io == 0)
		fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if ((type == T_IN_NODE || type == T_DOUBLE_IN_NODE)
		&& io == 1)
		fd = open(name, O_RDONLY, 0644);
	return (fd);
}

int	ft_getredir(t_ast *tree, int io)
{
	t_ast	**cpy;
	int		fd;

	fd = -1;
	if (!tree)
		return (0);
	cpy = ft_calloc(1, sizeof(void *));
	*cpy = tree;
	while (*cpy)
	{
		fd = ft_open_file((*cpy)->data, (*cpy)->type, io, fd);
		if (fd == -1)
		{
			perror((*cpy)->data);
			g_env.l_cod = 1;
			free(cpy);
			return (-1);
		}
		if (io == 0)
			(*cpy) = (*cpy)->right;
		else if (io == 1)
			(*cpy) = (*cpy)->left;
	}
	free(cpy);
	return (fd);
}

void	ft_dupsaux(t_l_fd *l_fd, int fd[], t_l_fd *r_fd)
{
	if (l_fd)
	{
		dup2(l_fd->fd[READ_END], 0);
		close(l_fd->fd[READ_END]);
	}
	if (r_fd)
		dup2(fd[WRITE_END], 1);
	close(fd[WRITE_END]);
}	

void	ft_dups(t_l_fd *l_fd, int fd[], t_l_fd *r_fd, t_ast *tree)
{
	int		fdesc;

	sig_child();
	close(fd[READ_END]);
	ft_dupsaux(l_fd, fd, r_fd);
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
}
