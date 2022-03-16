#include <minishell.h>

void	ft_use_builtins(t_ast *tree, int fd)
{
	if (ft_strncmp(tree->data, "pwd", 3) == 0)
		ft_pwd(fd);
	else if (ft_strncmp(tree->data, "echo", 4) == 0)
		ft_echo(tree, fd);
	else if (ft_strncmp(tree->data, "exit", 4) == 0)
		ft_exit();
	else if (ft_strncmp(tree->data, "env", 3) == 0)
		ft_env(fd);
	else if (ft_strncmp(tree->data, "unset", 5) == 0)
		ft_unset(tree);
	else if (ft_strncmp(tree->data, "export", 5) == 0)
		ft_export(tree, fd);
	else if (ft_strncmp(tree->data, "cd", 2) == 0)
		ft_cd(tree->left);
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
	if (!ft_strncmp(tree->data, "unset", 5) && vars != NULL)
		return (1);
	if ((!ft_strncmp(tree->data, "env", 3)
			|| !ft_strncmp(tree->data, "exit", 4)) && !vars)
		return (1);
	else
		return (0);
}

int	ft_exec_builtin(t_ast *tree, int pip, t_l_fd *r_fd, int fd[])
{
	int	fdesc;

	if (pip)
		fdesc = fd[WRITE_END];
	fdesc = ft_getredir(tree->right->right, 0);
	if (!fdesc)
		fdesc = 1;
	ft_use_builtins(tree, fdesc);
	close(fd[WRITE_END]);
	if (pip)
	{
		r_fd->fd[READ_END] = fd[READ_END];
		return (0);
	}
	close(fd[READ_END]);
	free(r_fd);
	r_fd = NULL;
	return (0);
}

