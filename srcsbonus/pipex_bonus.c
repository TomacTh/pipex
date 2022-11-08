/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:00:55 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/18 18:10:38 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	infile(t_data *params)
{
	pid_t	pid;

	create_pipe(params);
	if (params->infile == -1)
		perror(params->shell);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_exit("fork error", params, 1);
		if (!pid)
		{
			dup2(params->in, 0);
			close(params->fd[0]);
			dup2(params->fd[1], 1);
			close(params->fd[1]);
			if (params->here_doc)
				exec_func(params, 3);
			else
				exec_func(params, 2);
		}
	}
	parent_process(params);
}

void	arg(t_data *params, int i)
{
	pid_t	pid;

	create_pipe(params);
	pid = fork();
	if (pid < 0)
		ft_exit("fork error", params, 1);
	if (!pid)
	{
		dup2(params->in, 0);
		close(params->fd[0]);
		dup2(params->fd[1], 1);
		close(params->fd[1]);
		exec_func(params, i);
	}
	parent_process(params);
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
			ft_exit("fork error", params, 1);
		if (!pid)
		{
			dup2(params->in, 0);
			close(params->in);
			dup2(params->outfile, 1);
			exec_func(params, params->ac - 2);
		}
	}
	close_fd(&params->in);
	free_split(params->paths, -1);
	if (params->outfile == -1)
		return (-1);
	return (pid);
}

int	end_program(t_data *params)
{
	pid_t	last;
	int		exit_stat;

	last = outfile(params);
	close_fd(&params->outfile);
	while(1);
	if (last != -1)
	{
		waitpid(last, &params->status, 0);
		exit_stat = WEXITSTATUS(params->status);
	}
	while (wait(0) != -1)
		;
	if (last == -1)
		return (EXIT_FAILURE);
	return (exit_stat);
}

int	main(int ac, char **av, char **envp)
{
	t_data	params;
	int		i;

	ft_bzero(&params, sizeof(params));
	init(&params, ac, av, envp);
	infile(&params);
	if (ac > params.min_param)
	{
		i = 2;
		if (params.here_doc)
			i = 3;
		while (++i < ac - 2)
			arg(&params, i);
	}
	if (params.here_doc)
		params.outfile = open(av[ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		params.outfile = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	return (end_program(&params));
}
