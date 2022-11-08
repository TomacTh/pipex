/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 21:52:28 by tcharvet          #+#    #+#             */
/*   Updated: 2021/06/23 14:49:06 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (*(unsigned char *)s1 == *(
			unsigned char *)s2 && *(unsigned char *)s1 && --n)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	ft_bzero(void *s, size_t n)
{
	while (n-- > 0)
		*(char *)s++ = 0;
}

char	*get_path(char **env)
{
	char	*res;
	int		i;

	i = 0;
	res = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			res = env[i] + 5;
			break ;
		}
		++i;
	}
	return (res);
}

char	*get_shell(char **env)
{
	int		i;
	int		y;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("SHELL=", env[i], 5))
			break ;
		++i;
	}
	y = ft_strlen(env[i]);
	while (env[i][y] != '/')
		y--;
	return (&env[i][y + 1]);
}
