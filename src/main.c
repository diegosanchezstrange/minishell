
#include <minishell.h>
#include <readline/readline.h>

char	*ft_get_path(char *arg)
{
	char	*env;
	char	**path;
	char	*command;

	if (access(arg, F_OK) == 0)
		return (arg);
	env = getenv("PATH");
	if (!env)
		return ("");
	path = ft_split(env, ':');
	while (*path)
	{
		command = ft_strjoin(*path, ft_strjoin("/", arg));
		if (access(command, F_OK) == 0)
			return (command);
		path++;
	}
	return ("");
}

int	ft_execute(char **tokens)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(ft_get_path(tokens[0]), tokens, NULL);
		perror(tokens[0]);
		exit(0);
	}
	else if (pid < 0)
	{
		perror("minish");
		return (0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return (1);
	}
}

char	**ft_get_tokens(char *line)
{
	char	**tokens;

	tokens = ft_split(line,  ' ');
	return (tokens);
}

int	main()
{
	char	**tokens;
	char	*line;
	int		status;

	status = 1;
	while (status)
	{
		line = readline("$ ");
		tokens = ft_get_tokens(line);
		ft_execute(tokens);
	}
	return (0);
}
