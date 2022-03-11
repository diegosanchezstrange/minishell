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
	char	*aux;

	var = ft_getenv(name);
	if (!var)
		tmp = ft_substr(token, 0, i);
	else
	{
		aux = ft_substr(token, 0, i);
		tmp = ft_strjoin(aux, var);
		free(aux);
	}
	free(var);
	var = tmp;
	aux = ft_substr(token, i + num + 1, ft_strlen(token));
	tmp = ft_strjoin(var, aux);
	free(aux);
	free(var);
	free(token);
	return (tmp);
}

void	ft_extend_vars(char **token, t_pstatus *status)
{
	int		i;
	int		num;
	char	*aux;
	int		squotes;

	i = 0;
	num = 0;
	squotes = 1;
	while ((*token)[i])
	{
		if ((*token)[i] == '\'')
			squotes++;
		if ((*token)[i] == '$' && squotes % 2 != 0)
		{
			if ((*token)[i + 1] == '?')
				*token = ft_join_env_var(aux, *token, i, num);
			else
			{
				aux = ft_get_env_var((*token) + i + 1, &num);
				if (aux)
					*token = ft_join_env_var(aux, *token, i, num);
				free(aux);
			}
		}
		if ((*token)[i])
			i++;
	}
}
