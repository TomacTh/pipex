/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 21:52:37 by tcharvet          #+#    #+#             */
/*   Updated: 2021/06/24 14:09:09 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_exit(char *str, t_data *params, int code)
{
	if (code > 0)
		perror(str);
	else if (!code)
		ft_putstr_fd(str, 2);
	while (wait(0) != -1)
		;
	close_all(params);
	free_split(params->paths, -1);
	free_split(params->cmds, -1);
	exit(EXIT_FAILURE);
}

void	prepare_paths(t_data *params)
{
	int	i;

	i = 0;
	while (params->paths[i])
	{
		params->paths[i] = ft_strjoin_free_s1(params->paths[i], "/bash");
		if (!params->paths[i])
			ft_exit("malloc error", params, 1);
		i++;
	}
}

void	check_args(t_data *params, char **av, int ac)
{
	params->min_param = 5;
	if (!strcmp(av[1], "here_doc"))
	{
		params->here_doc = 1;
		params->min_param++;
	}
	else
		params->infile = open(av[1], O_RDONLY);
	if (ac < params->min_param)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	here_doc_func(t_data *params)
{	
	char	*str;
	int		res;

	str = 0;
	if (pipe(params->here_doc_pipe) == -1)
		ft_exit("pipe error", params, 1);
	while (1)
	{
		write(1, "> ", 2);
		res = get_next_line(0, &str);
		if (res < 1 || !strcmp(params->arg[2], str))
			break ;
		write(params->here_doc_pipe[1], str, strlen(str));
		write(params->here_doc_pipe[1], "\n", 1);
		free(str);
	}
	if (res == -1)
		ft_exit("get_next_line_error", params, 1);
	else if (res == 0)
		ft_putstr_fd("bash: warning: here_doc delimited by EOF\n", 2);
	free(str);
	close_fd(&params->here_doc_pipe[1]);
	params->in = params->here_doc_pipe[0];
}

void	init(t_data *params, int ac, char **av, char **envp)
{
	check_args(params, av, ac);
	params->in = -1;
	params->arg = av;
	params->envp = envp;
	params->ac = ac;
	params->path = get_path(envp);
	params->shell = get_shell(envp);
	params->paths = ft_split(params->path, ':');
	params->fd[0] = -1;
	params->fd[1] = -1;
	params->here_doc_pipe[0] = -1;
	params->here_doc_pipe[1] = -1;
	if (!params->paths)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	prepare_paths(params);
	if (!params->here_doc)
		params->in = params->infile;
	else
		here_doc_func(params);
}
