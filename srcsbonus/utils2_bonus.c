/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:57:06 by tcharvet          #+#    #+#             */
/*   Updated: 2021/06/24 13:55:33 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	create_pipe(t_data *params)
{
	if (pipe(params->fd) < 0)
		return (ft_exit("pipe error", params, 1));
	return (0);
}

void	close_all(t_data *params)
{
	close_fd(&params->fd[0]);
	close_fd(&params->fd[1]);
	if (params->in != params->infile || params->in != params->here_doc_pipe[0])
		close_fd(&params->in);
	close_fd(&params->here_doc_pipe[1]);
	close_fd(&params->here_doc_pipe[0]);
	close_fd(&params->infile);
	close_fd(&params->outfile);
}

void	parent_process(t_data *params)
{
	close_fd(&params->fd[1]);
	close_fd(&params->in);
	params->in = params->fd[0];
	params->fd[0] = -1;
}

void	exec_func(t_data *params, int n)
{
	int		i;
	char	**cmd_name;

	i = -1;
	params->cmds = (char *[]){"bash", "-c", params->arg[n], NULL};
	while (params->paths[++i])
		execve(params->paths[i], params->cmds, params->envp);
	ft_putstr_fd(params->shell, 2);
	ft_putstr_fd(": command not found: ", 2);
	cmd_name = ft_split(params->arg[n], ' ');
	if (!cmd_name)
		ft_exit("malloc error", params, 1);
	ft_putstr_fd(cmd_name[0], 2);
	ft_putstr_fd("\n", 2);
	free_split(cmd_name, -1);
	exit(EXIT_FAILURE);
}
