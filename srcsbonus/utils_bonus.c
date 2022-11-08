/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 21:48:10 by tcharvet          #+#    #+#             */
/*   Updated: 2021/06/24 13:55:29 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*(unsigned char *)s1 == *(
			unsigned char *)s2 && *(unsigned char *)s1)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	ptr = (malloc(sizeof(void) * (size * count)));
	if (!ptr)
		return (0);
	i = 0;
	while (i < (size * count))
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	size;

	size = ft_strlen(s);
	new = ft_calloc(sizeof(char) * (size + 1), 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, s, size);
	return (new);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdst;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if (dst != src)
	{
		while (n--)
		{
			*pdst = *psrc;
			++pdst;
			++psrc;
		}
	}
	return (dst);
}
