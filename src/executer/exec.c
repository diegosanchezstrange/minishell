#include <minishell.h>

void	ft_exec_command(t_ast *node, int pipeRedir)
{
	int	pid;
	int	fd[2];

	if (!node)
		return ;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		//ft_mange_inputs(node->right->left);
		close(READ_END);
		if (pipeRedir)
			dup2(fd[WRITE_END], 0);
		close(fd[WRITE_END]);
		//ft_mange_outputs(node->right->right);
	}
	else
	{

	}
}

void	ft_exec_tree(t_ast *tree, int pipe)
{
	if (tree->type == T_PIPE_NODE)
	{
		ft_exec_tree(tree->left, 1);
		ft_exec_tree(tree->right, 0);
	}
	if (tree->type == T_COMMAND_NODE)
		ft_exec_command(tree, pipe);
}
