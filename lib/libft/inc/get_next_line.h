/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:47:45 by dsanchez          #+#    #+#             */
/*   Updated: 2021/10/26 21:08:55 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_strlen(char const *s);
char	*get_next_line(int fd);

#endif
