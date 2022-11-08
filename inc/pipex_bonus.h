/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:33:02 by tcharvet          #+#    #+#             */
/*   Updated: 2021/10/27 19:59:50 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef struct s_data
{
	char	**arg;
	char	**envp;
	char	*path;
	char	*shell;
	char	**paths;
	char	**cmds;
	int		ac;
	int		fd[2];
	int		here_doc_pipe[2];
	int		here_doc;
	int		min_param;
	int		in;
	int		infile;
	int		outfile;
	int		status;
}	t_data;

typedef struct s_gnl
{
	char	*buf;
	size_t	i;
	size_t	max;
	int		y;
}			t_gnl;

char	**free_split(char **strs, int len);
char	**ft_split(char const *s, char c);
int		get_next_line(int fd, char **line);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free_s1(char *s1, char *s2);

size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *s);

void	prepare_paths(t_data *params);
void	init(t_data *params, int ac, char **av, char **envp);

void	exec_func(t_data *params, int n);
void	parent_process(t_data *params);
int		create_pipe(t_data *params);
void	here_doc_func(t_data *params);

char	*get_path(char **env);
char	*get_shell(char **env);

void	close_fd(int *fd);
int		ft_exit(char *str, t_data *params, int code);
void	close_all(t_data *params);

#endif
