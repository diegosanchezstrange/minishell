/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:47:40 by dsanchez          #+#    #+#             */
/*   Updated: 2021/10/26 21:09:08 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)malloc(nmemb * size);
	if (!res)
		return (NULL);
	while (i < size * nmemb)
	{
		res[i] = 0;
		i++;
	}
	return ((void *)res);
}

int	next_nl(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_res(char *line)
{
	char	*res;
	int		l;
	int		i;

	i = 0;
	l = 0;
	if (!line)
		return (NULL);
	while (line[l] && line[l] != '\n')
		l++;
	if (line[l] == '\n')
		l++;
	res = malloc(l + 1);
	if (!res)
		return (NULL);
	while (i < l)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*get_line(char *line)
{
	int		l;
	int		i;
	char	*nline;

	i = 0;
	l = 0;
	if (!line)
		return (NULL);
	while (line[l] && line[l] != '\n')
		l++;
	if (line[l] == '\n')
		l++;
	nline = malloc(ft_strlen_gnl(line) - l + 1);
	while (line[l])
		nline[i++] = line[l++];
	nline[i] = 0;
	free(line);
	if (nline[0] != 0)
		return (nline);
	else
	{
		free(nline);
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	char		*buff;
	int			r;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	r = 1;
	while (r != 0 && next_nl(line) == -1)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[r] = '\0';
		line = ft_strjoin_gnl(line, buff);
	}
	free(buff);
	buff = get_res(line);
	line = get_line(line);
	return (buff);
}
