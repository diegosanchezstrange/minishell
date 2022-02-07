#include <minishell.h>

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

void	ft_free_split(char **s)
{
	char	**str;

	str = s;
    while (*str)
	{
		free(*str);
		str++;
	}
	free(s);
}

char	**ft_envmatrix()
{
	char	**environ;
	int		i;
	t_list	*cpy;

	environ = ft_calloc(ft_lstsize(g_env) + 1, sizeof(char *));
	i = 0;
	if (!g_env)
	{
		free(environ);
		return NULL;
	}
	cpy = g_env;
	while (g_env)
	{
		environ[i++] = ft_strdup(g_env->content);
		g_env = g_env->next;
	}
	environ[i]= "\0";
	g_env = cpy;
	return (environ);
}

void	ft_exec_command(t_ast *node, int pipeRedir)
{
	int		pid;
	int		fd[2];
	char	**cmd;
	char	**environ;

	if (!node)
		return ;
	pipe(fd);
	pid = fork();
	environ = ft_envmatrix();
	if (pid == 0)
	{
		cmd = ft_return_cmd(node->left, node->data);
		//ft_mange_inputs(node->right->left);
		close(READ_END);
		if (pipeRedir)
			dup2(fd[WRITE_END], 0);
		close(fd[WRITE_END]);
		printf("CMD : %s\n", cmd[0]);
		printf("CMD : %s\n", cmd[1]);
		execve(cmd[0], cmd, environ);
		ft_free_split(environ);
		perror(cmd[0]);
		ft_free_split(cmd);
		exit(1);

		//ft_mange_outputs(node->right->right);
	}
	else
	{
		close(fd[WRITE_END]);
		if (pipeRedir)
			dup2(fd[READ_END], 0);
		close(fd[READ_END]);
		waitpid(pid, NULL, 0);
	}
}

void	ft_exec_tree(t_ast *tree, int pipe)
{
	//printf("command : %s\n", tree->data);
	//printf("param : %s\n", tree->left->data);
	if (tree->type == T_PIPE_NODE)
	{
		ft_exec_tree(tree->left, 1);
		ft_exec_tree(tree->right, 0);
	}
	if (tree->type == T_COMMAND_NODE)
	{
		if (ft_strnstr(tree->data, "cdpwdechoexitunsetenvexport", 
					ft_strlen(tree->data)))
			ft_use_builtins(tree);
		else
			ft_exec_command(tree, pipe);
	}
}
