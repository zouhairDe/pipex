/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:32:33 by zouddach          #+#    #+#             */
/*   Updated: 2024/03/10 00:26:47 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_backupenv(t_pipex *pipex)
{
	pipex->env_path = malloc(sizeof(char *) * 2);
	pipex->env_path[0] = ft_strjoin("PATH=", "/Users/zouddach/.npm-global/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:\
/sbin:/usr/local/munki:/Library/Apple\
/usr/bin:/Users/zouddach/.npm-global/bin");
	pipex->env_path[1] = NULL;
	get_path(pipex, pipex->env_path);
}

void	second_shild(t_pipex *pipex, int *fd, pid_t pid)
{
	int		i;
	int		file;

	pid = fork();
	if (pid == 0)
	{
		i = 0;
		file = open(pipex->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		close(fd[1]);
		(dup2(file, 1), dup2(fd[0], 0));
		(close(fd[0]), close(file));
		while (i < pipex->path_length)
		{
			pipex->env_path[i] = ft_strjoin(pipex->env_path[i], pipex->cmd2[0]);
			if (access(pipex->env_path[i], F_OK) == -1)
				i++;
			else
				break ;
		}
		if (!pipex->cmd2[0] || i == pipex->path_length)
			(perror(pipex->cmd2[0]), exit(EXIT_FAILURE));
		execve(pipex->env_path[i], pipex->cmd2, NULL);
	}
	else if (pid < 0)
		(ft_free_all(pipex), perror("Fork"), exit(EXIT_FAILURE));
}

void	first_child(t_pipex *pipex, int *fd)
{
	int		d;
	int		i;

	d = open(pipex->infile, O_RDONLY);
	if (d < 0)
		perror(pipex->infile);
	i = 0;
	close(fd[0]);
	dup2(fd[1], 1);
	dup2(d, 0);
	close(fd[1]);
	close(d);
	while (i < pipex->path_length)
	{
		pipex->env_path[i] = ft_strjoin(pipex->env_path[i], pipex->cmd1[0]);
		if (access(pipex->env_path[i], F_OK) == -1)
			i++;
		else
			break ;
	}
	if (!pipex->cmd1[0] || i == pipex->path_length)
		(perror(pipex->cmd1[0]), exit(EXIT_FAILURE));
	execve(pipex->env_path[i], pipex->cmd1, NULL);
}
