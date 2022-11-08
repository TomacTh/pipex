/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 22:18:08 by tcharvet          #+#    #+#             */
/*   Updated: 2021/06/22 16:50:45 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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
	char	**cmds;
	char	**paths;
	int		ac;
	int		fd[2];
	int		infile;
	int		outfile;
	int		status;
}	t_data;

char	**free_split(char **strs, int len);
char	**ft_split(char const *s, char c);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free_s1(char *s1, char *s2);

size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);

void	exec_func(t_data *params, int n);
void	prepare_paths(t_data *params);
void	parent_process(t_data *params);

char	*get_path(char **env);
char	*get_shell(char **env);

void	close_fd(int *fd);
int		ft_exit(char *str, t_data *params);
void	close_all(t_data *params);

#endif
