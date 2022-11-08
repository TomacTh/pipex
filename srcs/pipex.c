/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:00:55 by tcharvet          #+#    #+#             */
/*   Updated: 2021/06/24 15:30:35 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infile(t_data *params)
{
	pid_t	pid;

	if (pipe(params->fd) < 0)
		ft_exit("pipe error", params);
	if (params->infile == -1)
		perror(params->shell);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_exit("fork error", params);
		if (!pid)
		{	
			close(params->fd[0]);
			dup2(params->infile, 0);
			dup2(params->fd[1], 1);
			close(params->fd[1]);
			exec_func(params, 2);
		}
	}
	close_fd(&params->infile);
	close(params->fd[1]);
}

pid_t	outfile(t_data *params)
{
	pid_t	pid;

	if (params->outfile == -1)
		perror(params->shell);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_exit("fork error", params);
		if (!pid)
		{
			dup2(params->fd[0], 0);
			dup2(params->outfile, 1);
			close(params->fd[0]);
			exec_func(params, params->ac - 2);
		}
	}
	close(params->fd[0]);
	free_split(params->paths, -1);
	if (params->outfile == -1)
		return (-1);
	return (pid);
}

void	init(t_data *params, int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	params->infile = open(av[1], O_RDONLY);
	params->arg = av;
	params->envp = envp;
	params->ac = ac;
	params->path = get_path(envp);
	params->shell = get_shell(envp);
	params->paths = ft_split(params->path, ':');
	if (!params->paths)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	prepare_paths(params);
}

int	main(int ac, char **av, char **envp)
{
	t_data	params;
	pid_t	last;
	int		exit_stat;

	ft_bzero(&params, sizeof(params));
	init(&params, ac, av, envp);
	infile(&params);
	params.outfile = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	last = outfile(&params);
	close_fd(&params.outfile);
	if (last != -1)
	{
		waitpid(last, &params.status, 0);
		exit_stat = WEXITSTATUS(params.status);
	}
	while (wait(0) != -1)
		;
	if (last == -1)
		return (EXIT_FAILURE);
	return (exit_stat);
}
