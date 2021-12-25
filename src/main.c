
#include <minishell.h>
#include <readline/readline.h>

int	main()
{
	char	*line;
	int		status;

	status = 1;
	while (status)
	{
		line = readline("$ ");
	}
	return (0);
}
