/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:18:11 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/09 18:59:10 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	error(char **line, int fd, char *buf)
{
	if (!line || fd < 0 || fd > 256 || !buf)
	{
		if (buf)
			free(buf);
		return (1);
	}
	return (0);
}

static int	alloc_more(char *buf, size_t *max)
{
	char	*tmp;

	tmp = calloc(sizeof(char) * (*max + 4096), 1);
	if (!tmp)
	{
		free(buf);
		return (-1);
	}
	ft_memcpy(tmp, buf, *max);
	free(buf);
	buf = tmp;
	*max += 4096;
	return (0);
}

static int	return_result(char **line, t_gnl *gnl)
{
	*line = ft_strdup(gnl->buf);
	free(gnl->buf);
	if (!*line)
		return (-1);
	return (gnl->y);
}

static int	return_gnl(int fd, char **line, t_gnl *gnl)
{
	while (gnl->y > 0)
	{
		gnl->y = read(fd, &gnl->buf[gnl->i], 1);
		if (gnl->buf[gnl->i] == '\n')
		{
			gnl->buf[gnl->i] = '\0';
			*line = ft_strdup(gnl->buf);
			if (!*line)
			{
				free(gnl->buf);
				return (0);
			}
			free(gnl->buf);
			return (1);
		}
		if (gnl->i == gnl->max - 1)
		{
			if (alloc_more(gnl->buf, &gnl->max))
				return (-1);
		}
		gnl->i++;
	}
	return (return_result(line, gnl));
}

int	get_next_line(int fd, char **line)
{
	t_gnl	gnl;

	ft_bzero(&gnl, sizeof(gnl));
	gnl.max = 4096;
	gnl.buf = ft_calloc(gnl.max, 1);
	if (error(line, fd, gnl.buf))
		return (-1);
	gnl.i = 0;
	gnl.y = 1;
	return (return_gnl(fd, line, &gnl));
}
