#include <minishell.h>

char	*ft_get_env_var(char *token, int *num)
{
	int	i;

	i = 0;
	if (ft_isalpha(token[i]) || token[i] == '_')
		i++;
	else
	{
		*num = 0;
		return (NULL);
	}
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	*num = i;
	return (ft_substr(token, 0, *num));
}

char	*ft_join_env_var(char *name, char *token, int i, int num)
{
	char	*var;
	char	*tmp;

	var = getenv(name);
	if (!var)
		return (token);
	tmp = ft_strjoin(ft_substr(token, 0, i), var);
	var = tmp;
	tmp = ft_strjoin(var, ft_substr(token, i + num + 1, ft_strlen(token)));
	free(var);
	free(token);
	return (tmp);
}

void	ft_extend_vars(char **token)
{
	int		i;
	int		num;
	char	*aux;

	i = 0;
	num = 0;
	while ((*token)[i])
	{
		if ((*token)[i] == '$')
		{
			aux = ft_get_env_var((*token) + i + 1, &num);
			*token = ft_join_env_var(aux, *token, i, num);
		}
		i++;
	}
}
