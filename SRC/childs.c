/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:32:33 by zouddach          #+#    #+#             */
/*   Updated: 2024/03/04 16:21:43 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_shild(t_pipex *pipex, int *fd, pid_t pid)
{
	int		i;
	char	*r;

	pid = fork();
	if (pid == 0)
	{
		i = 0;
		close(fd[1]);
		dup2(fd[0], 0);
		dup2(open(pipex->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666), 1);
		close(fd[0]);
		while (i < pipex->path_length)
		{
			r = ft_strjoin(pipex->env_path[i], pipex->cmd2[0]);
			if (access(r, F_OK) == -1)
				i++;
			else
				break ;
			free(r);
		}
		execve(r, pipex->cmd2, NULL);
	}
	else if (pid < 0)
		(ft_free_all(pipex), perror("Fork"), exit(EXIT_FAILURE));
}

void	first_child(t_pipex *pipex, int *fd)
{
	int		d;
	int		i;
	char	*r;

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
		r = ft_strjoin(pipex->env_path[i], pipex->cmd1[0]);
		if (access(r, F_OK) == -1)
			i++;
		else
			break ;
		free(r);
	}
	execve(r, pipex->cmd1, NULL);
}
