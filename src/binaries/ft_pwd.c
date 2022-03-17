/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:01:39 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/17 15:05:51 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pwd(int fd)
{
	char	*path;

	path = getcwd(0, 0);
	if (path)
	{
		write(fd, path, ft_strlen(path));
		write(fd, "\n", 1);
	}
	free(path);
}
