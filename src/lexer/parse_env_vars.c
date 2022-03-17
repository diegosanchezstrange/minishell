/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:58:35 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/17 16:04:23 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_join_err_code(char *token, int i)
{
	char	*num;
	char	*tmp;
	char	*aux;

	num = ft_itoa(g_env.l_cod);
	tmp = ft_substr(token, 0, i);
	aux = ft_strjoin(tmp, num);
	free(tmp);
	free(num);
	tmp = ft_substr(token, i + ft_strlen(num) + 1, ft_strlen(token));
	num = ft_strjoin(aux, tmp);
	free(token);
	free(tmp);
	free(aux);
	return (num);
}

void	ft_process_env_vars(char **token, int i)
{
	int		num;
	char	*aux;

	num = 0;
	if (!(*token)[i + 1])
		return ;
	if ((*token)[i + 1] == '?')
		*token = ft_join_err_code(*token, i);
	else
	{
		aux = ft_get_env_var((*token) + i + 1, &num);
		if (aux)
			*token = ft_join_env_var(aux, *token, i, num);
		free(aux);
	}
}

void	ft_extend_vars(char **token)
{
	int		i;
	int		squotes;
	int		dquotes;

	i = 0;
	squotes = 1;
	dquotes = 1;
	while ((*token)[i])
	{
		if ((*token)[i] == '\'')
			squotes++;
		if ((*token)[i] == '\"')
			dquotes++;
		if ((*token)[i] == '$' && squotes % 2 != 0)
			ft_process_env_vars(token, i);
		else if ((*token)[i] == '$'
				&& (squotes % 2 != 0 && (dquotes == 1 || dquotes % 2 == 0)))
			ft_process_env_vars(token, i);
		if ((*token)[i])
			i++;
	}
}
