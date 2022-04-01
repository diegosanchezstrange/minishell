#include <minishell.h>

int	ft_valid_var_name(char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (0);
	if (ft_isalpha(name[i]) || name[i] == '_')
		i++;
	else
		return (0);
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
