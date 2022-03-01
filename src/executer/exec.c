#include <minishell.h>
#include <errno.h>

char	*ft_strjoin_path(char *path, char *cmd)
{
	char	*sol;
	char	*tmp;

	tmp = ft_strjoin("/", cmd);
	sol = ft_strjoin(path, tmp);
	free(tmp);
	return (sol);
}

char	*ft_getpath(char **envp, char *cmd)
{
	char	**path;
	char	**tmp;
	char	*command;

	if (access(cmd, F_OK) == 0)
		return (cmd);
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
			return (command);
		free(command);
		path++;
	}
	ft_free_split(tmp);
	return ("");
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
	char	**environ;

	if (!node)
		return ;
	environ = ft_envmatrix();
	cmd = ft_return_cmd(node->left, node->data);
	execve(ft_getpath(environ, cmd[0]), cmd, environ);
	perror(cmd[0]);
	ft_free_split(environ);
	ft_free_split(cmd);
	exit(1);
}

void	ft_pipe_here_doc(char *delimiter)
{
	char	*line;
	int		fd[2];
	int		pid;
	size_t	l;

	pipe(fd);
	l = 0;
	pid = fork();
	if (pid == 0)
	{
		close(fd[READ_END]);
		while (1)
		{
			line = get_next_line(0);
			l = ft_strlen(line);
			if (l)
				line[l - 1] = 0;
			if (l < ft_strlen(delimiter))
				l = ft_strlen(delimiter);
			if (ft_strncmp(line, delimiter, l) == 0)
				break ;
			write(fd[WRITE_END], line, ft_strlen(line));
			free(line);
		}
		free(line);
		exit(0);
	}
	else
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], 0);
		close(fd[READ_END]);
		waitpid(pid, NULL, 0);
	}
}

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
		printf("FILE : %s\n", (*cpy)->data);
		printf("FILE R : %s\n", (*cpy)->left->data);
		if ((*cpy)->type == T_OUT_NODE && io == 0)
			fd = open((*cpy)->data, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*cpy)->type == T_DOUBLE_OUT_NODE && io == 0)
			fd = open((*cpy)->data, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*cpy)->type == T_IN_NODE && io == 1)
			fd = open((*cpy)->data, O_RDONLY , 0644);
		if ((*cpy)->type == T_DOUBLE_IN_NODE && io == 1)
		{
			ft_pipe_here_doc((*cpy)->data);
			fd = 0;
		}
		if (fd == -1)
			return (0);
		//printf("TRAZA\n");
		(*cpy) = (*cpy)->right;
	}
	return (fd);
}
static void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
}

static void	my_prompt(int n)
{
	if (n == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
static void my_signal(void)
{

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, my_prompt);
}
void	ft_exec_tree(t_ast *tree, int pip)
{
	int	fdesc;
	int	pid;
	int	fd[2];

	if (tree->type == T_PIPE_NODE)
	{
		//printf("EJECUTANDO PIPE\n");
		ft_exec_tree(tree->left, 1);
		//printf("first: %s\n", tree->left->data);
		ft_exec_tree(tree->right, 0);
		//printf("second: %s\n", tree->right->data);
	}
	if (tree->type == T_COMMAND_NODE)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			my_signal();
			close(fd[READ_END]);
			if (pip == 1)
				dup2(fd[WRITE_END], 1);
			close(fd[WRITE_END]);
			fdesc = ft_getredir(tree->right->right, 0);
			if (fdesc)
				dup2(fdesc, 1);
			fdesc = ft_getredir(tree->right->left, 1);
			if (fdesc)
				dup2(fdesc, 0);
			if (ft_strnstr("envpwdechoexitunsetexport", tree->data,
						25) != NULL && valid_builtins(tree) == 1)
			{
				ft_use_builtins(tree);
				exit(0);
			}
			else
				ft_exec_command(tree);
		}
		else
		{
			sig_ignore();
			close(fd[WRITE_END]);
			if (pip)
				dup2(fd[READ_END], 0);
			close(fd[READ_END]);
			waitpid(pid, NULL, 0);
		}
	}
}
