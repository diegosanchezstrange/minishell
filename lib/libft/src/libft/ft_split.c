/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:40:07 by dsanchez          #+#    #+#             */
/*   Updated: 2021/09/15 20:42:00 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	fletter;
	int	i;
	int	count;

	fletter = -1;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (fletter == -1 && s[i] != c)
			fletter = i;
		else if (fletter != -1 && s[i] == c)
		{
			fletter = -1;
			count++;
		}
		i++;
	}
	if (fletter != -1)
		count++;
	return (count);
}

static char	*get_word(char *s, char c, int *i)
{
	int		count;
	int		j;
	char	*sol;

	count = 0;
	j = 0;
	while (s[count] && s[count] != c)
	{
		count++;
	}
	*i = *i + count;
	sol = (char *)malloc(count + 1);
	if (!(sol))
		return (NULL);
	while (j < count)
	{
		sol[j] = s[j];
		j++;
	}
	sol[j] = 0;
	return (sol);
}

char	**ft_split(char const *s, char c)
{
	char	**sol;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	sol = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!(sol))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
			sol[j++] = get_word((char *)&s[i], c, &i);
		else
			i++;
	}
	sol[j] = NULL;
	return (sol);
}
