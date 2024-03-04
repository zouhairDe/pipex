/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:27:09 by zouddach          #+#    #+#             */
/*   Updated: 2024/03/04 23:48:47 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->path_length)
		free(pipex->env_path[i++]);
	free(pipex->env_path);
	i = 0;
	while (pipex->cmd1[i])
		free(pipex->cmd1[i++]);
	free(pipex->cmd1);
	i = 0;
	while (pipex->cmd2[i])
		free(pipex->cmd2[i++]);
	free(pipex->cmd2);
}

void	simulate_pipex(t_pipex *pipex)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error: Pipe failed\n", 2);
		free(pipex->cmd1);
		free(pipex->cmd2);
		free(pipex->env_path);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(pipex->cmd1);
		free(pipex->cmd2);
		free(pipex->env_path);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		first_child(pipex, fd);
	else
		second_shild(pipex, fd, pid);
	ft_free_all(pipex);
	close(fd[0]);
	close(fd[1]);
}

void	add_slash(char **path)
{
	int		i;
	int		j;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
		{
			j = 0;
			while (path[j])
				free(path[j++]);
			free(path);
			perror("Malloc");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	get_path(t_pipex *pipex, char **env)
{
	int	i;

	i = 0;
	pipex->path_length = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pipex->env_path = ft_split(env[i] + 5, ':');
			add_slash(pipex->env_path);
			i = 0;
			while (pipex->env_path[i++])
				pipex->path_length++;
			return ;
		}
		i++;
	}
	ft_putstr_fd("Error: Cant find PATH\n", 2);
	free(pipex->cmd1);
	free(pipex->cmd2);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (0);
	}
	if (!env[0] || !env)
	{
		ft_putstr_fd("Error: No environment\n", 2);
		return (0);
	}
	pipex.cmd1 = ft_split(av[2], ' ');
	pipex.cmd2 = ft_split(av[3], ' ');
	pipex.infile = av[1];
	pipex.outfile = av[4];
	if (access(pipex.infile, R_OK) == -1)
	{
		ft_putstr_fd("Error: Cant access files\n", 2);
		exit(EXIT_FAILURE);
	}
	get_path(&pipex, env);
	simulate_pipex(&pipex);
	wait(NULL);
	return (0);
}
