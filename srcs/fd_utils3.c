/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 22:06:41 by tcharvet          #+#    #+#             */
/*   Updated: 2021/06/22 17:09:18 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_exit(char *str, t_data *params)
{
	while (wait(0) != -1)
		;
	perror(str);
	close_all(params);
	free_split(params->paths, -1);
	exit(EXIT_FAILURE);
}

void	close_all(t_data *params)
{
	close_fd(&params->fd[0]);
	close_fd(&params->fd[1]);
	close_fd(&params->infile);
	close_fd(&params->outfile);
}

void	prepare_paths(t_data *params)
{
	int	i;

	i = 0;
	while (params->paths[i])
	{
		params->paths[i] = ft_strjoin_free_s1(params->paths[i], "/bash");
		if (!params->paths[i])
			ft_exit("malloc error", params);
		i++;
	}
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
		ft_exit("malloc error", params);
	ft_putstr_fd(cmd_name[0], 2);
	ft_putstr_fd("\n", 2);
	free_split(cmd_name, -1);
	exit(EXIT_FAILURE);
}
