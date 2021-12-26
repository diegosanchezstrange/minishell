
#include <minishell.h>

char	**ft_get_tokens(char *line)
{
	char	**tokens;

	tokens = ft_split(line,  ' ');
	return (tokens);
}
