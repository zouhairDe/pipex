/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:27:09 by zouddach          #+#    #+#             */
/*   Updated: 2024/02/21 17:17:12 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(t_pipex *pipex)
{
	int i;

	i = 0;
	while(i < pipex->path_length)
		free(pipex->env_path[i++]);
	free(pipex->env_path);
	i = 0;
	while(pipex->cmd1[i])
		free(pipex->cmd1[i++]);
	free(pipex->cmd1);
	i = 0;
	while(pipex->cmd2[i])
		free(pipex->cmd2[i++]);
	free(pipex->cmd2);
}

void	second_shild(t_pipex *pipex, int *fd, pid_t pid)
{
	int 	i;
	char 	*r;

	pid = fork();
	if (pid == 0)
	{
		i = 0;
		close(fd[1]);
		dup2(fd[0], 0);
		dup2(open(pipex->outfile, O_WRONLY | O_TRUNC), 1);
		close(fd[0]);
		while(i < pipex->path_length)
		{
			r = ft_strjoin(pipex->env_path[i], pipex->cmd2[0]);
			if (access(r, F_OK) == -1)
				i++;
			else
				break;
			free(r);
		}
		execve(r, pipex->cmd2, NULL);
	}
	else
		ft_free_all(pipex);
}

void	first_child(t_pipex *pipex, int *fd)
{
	int d;
	int i;
	char *r;

	d = open(pipex->infile, O_RDONLY);
	if (d < 0)
		perror("haha");
		i = 0;
	close(fd[0]);
	dup2(fd[1], 1);
	dup2(d, 0);
	close(fd[1]);
	close(d);
	while(i < pipex->path_length)
	{
		r = ft_strjoin(pipex->env_path[i], pipex->cmd1[0]);
		if (access(r, F_OK) == -1)
			i++;
		else
			break;
		free(r);
	}
	execve(r, pipex->cmd1, NULL);
}

void	simulate_pipex(t_pipex *pipex)
{
	int		fd[2];
	pid_t	pid;

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
		ft_putstr_fd("Error: Fork failed\n", 2);
		free(pipex->cmd1);
		free(pipex->cmd2);
		free(pipex->env_path);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		first_child(pipex, fd);
	else
		second_shild(pipex, fd, pid);

}

void	add_slash(char **path)
{
	int i;
	int j;

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
	int i;

	i = 0;
	pipex->path_length = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pipex->env_path = ft_split(env[i] + 5, ':');
			add_slash(pipex->env_path);
			i = 0;
			while(pipex->env_path[i++])
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

void f(void)
{
	system("leaks pipex");
}

int main(int ac, char **av, char **env)
{
	t_pipex pipex;

	atexit(f);
	if (ac != 5)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (0);
	}
	pipex.cmd1 = ft_split(av[2], ' ');
	pipex.cmd2 = ft_split(av[3], ' ');
	pipex.infile = av[1];
	pipex.outfile = av[4];
	if (access(pipex.infile, R_OK) == -1 || access(pipex.outfile, W_OK) == -1)
	{
	 	ft_putstr_fd("Error: Cant access files\n", 2);
		exit(EXIT_FAILURE);
	}
	get_path(&pipex, env);
	simulate_pipex(&pipex);
	wait(NULL);
}
