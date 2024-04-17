/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 03:56:26 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/17 10:45:35 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_init_cmds(t_pipex *pipex, char **argv, char **env)
{
	pipex->infile = argv[1];
	pipex->outfile = argv[4];
	pipex->fd_out = open(pipex->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (pipex->fd_out == -1)
		perror(pipex->outfile);
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (!pipex->cmd1 || !pipex->cmd2)
	{
		ft_free_all(pipex);
		return (-1);
	}
	if (!env || !env[0])
		pipex->env_path = ft_split(BACKUP_ENV_PATH, ':');
	else
		ft_get_path(pipex, env);
	if (!pipex->env_path)
		return (-1);
	return (1);
}

int	ft_have_slash(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[0][i])
	{
		if (cmd[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	ft_init_struct(t_pipex *pipex)
{
	pipex->env_path = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->infile = NULL;
	pipex->outfile = NULL;
	pipex->fd_out = 0;
}
