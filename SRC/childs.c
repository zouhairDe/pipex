/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:32:33 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/15 13:20:55 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_save_lines2(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!ft_have_slash(pipex->cmd2))
	{
		while (pipex->env_path[i])
		{
			pipex->env_path[i] = ft_strjoin(pipex->env_path[i], pipex->cmd2[0]);
			if (access(pipex->env_path[i], F_OK) == -1)
				i++;
			else
				break ;
		}
		if (!pipex->cmd2[0] || pipex->env_path[i] == NULL)
		{
			perror(pipex->cmd2[0]);
			exit(EXIT_FAILURE);
		}
		execve(pipex->env_path[i], pipex->cmd2, NULL);
	}
	else
		execve(pipex->cmd2[0], pipex->cmd2, NULL);
	perror(pipex->cmd2[0]);
	ft_free_all(pipex);
	exit(EXIT_FAILURE);
}

void	ft_second_shild(t_pipex *pipex, int *fd, pid_t pid)
{
	int	file;

	pid = fork();
	if (pid == 0)
	{
		file = open(pipex->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (file < 0)
			perror(pipex->outfile);
		close(fd[1]);
		if (dup2(file, 1) < 0 || dup2(fd[0], 0) < 0)
		{
			close(fd[0]);
			close(file);
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		close(file);
		ft_save_lines2(pipex);
	}
	else if (pid < 0)
	{
		ft_free_all(pipex);
		perror("Fork");
		exit(EXIT_FAILURE);
	}
}

void	ft_save_lines(t_pipex *pipex)
{
	char	*path;
	int		i;

	i = 0;
	if (!ft_have_slash(pipex->cmd1))
	{
		while (pipex->env_path[i])
		{
			path = ft_strjoin(pipex->env_path[i], pipex->cmd1[0]);
			if (access(path, F_OK) != -1)
				break ;
			free(path);
			i++;
		}
		if (!pipex->cmd1[0] || path == NULL)
		{
			perror(pipex->cmd1[0]);
			exit(EXIT_FAILURE);
		}
		execve(path, pipex->cmd1, NULL);
	}
	execve(pipex->cmd1[0], pipex->cmd1, NULL);
	perror(pipex->cmd1[0]);
	exit(EXIT_FAILURE);
}

void	ft_first_child(t_pipex *pipex, int *fd)
{
	int	d;
	int	i;

	d = open(pipex->infile, O_RDONLY);
	if (d < 0)
		perror(pipex->infile);
	i = 0;
	close(fd[0]);
	if (dup2(fd[1], 1) < 0 || dup2(d, 0) < 0)
	{
		close(fd[1]);
		close(d);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	close(d);
	ft_save_lines(pipex);
}
