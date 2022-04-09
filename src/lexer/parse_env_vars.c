/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:25:20 by dsanchez          #+#    #+#             */
/*   Updated: 2022/04/09 15:25:24 by dsanchez         ###   ########.fr       */
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

int	ft_process_env_vars(char **token, int i)
{
	int		num;
	char	*aux;

	num = 0;
	if (!(*token)[i + 1])
		return (1);
	if ((*token)[i + 1] == '?')
		*token = ft_join_err_code(*token, i);
	else
	{
		aux = ft_get_env_var((*token) + i + 1, &num);
		if (aux)
			*token = ft_join_env_var(aux, *token, i, num);
		else
			return (0);
		free(aux);
	}
	return (1);
}

void	ft_extend_vars(char **token)
{
	int				i;
	t_lex_states	state;

	i = 0;
	state = P_NEUTRAL;
	while ((*token)[i])
	{
		if ((*token)[i] == '$' && (state == P_NEUTRAL || state == P_D_QUOTE))
		{
			if (!ft_process_env_vars(token, i) || (*token)[i] == '$')
				i++;
			continue ;
		}
		if ((*token)[i] == '\'' && state == P_NEUTRAL)
			state = P_S_QUOTE;
		else if ((*token)[i] == '\'' && state == P_S_QUOTE)
			state = P_NEUTRAL;
		if ((*token)[i] == '\"' && state == P_NEUTRAL)
			state = P_D_QUOTE;
		else if ((*token)[i] == '\"' && state == P_D_QUOTE)
			state = P_NEUTRAL;
		if ((*token)[i])
			i++;
	}
}
