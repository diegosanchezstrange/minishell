#include <minishell.h>

int	valid_variable(char  *data)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], data, ft_strlen(data)))
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(char	*data)
{
	if (!valid_variable(data))
		return ;
}
