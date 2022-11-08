/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 21:49:21 by tcharvet          #+#    #+#             */
/*   Updated: 2021/06/22 14:53:36 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*begin;

	if (!s1 || !s2)
		return (0);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	begin = str;
	while (*(char *)s1)
	{
		*str = *(char *)s1;
		s1++;
		str++;
	}
	while (*(char *)s2)
	{
		*str = *(char *)s2;
		s2++;
		str++;
	}
	*str = '\0';
	return (begin);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	close_fd(int *fd)
{
	if (*fd > -1)
	{
		close(*fd);
		*fd = -1;
	}
}
