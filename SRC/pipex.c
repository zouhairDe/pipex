/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:27:09 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/16 09:46:01 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->env_path && pipex->env_path[i])
		free(pipex->env_path[i++]);
	free(pipex->env_path);
	i = 0;
	while (pipex->cmd1 && pipex->cmd1[i])
		free(pipex->cmd1[i++]);
	free(pipex->cmd1);
	i = 0;
	while (pipex->cmd2 && pipex->cmd2[i])
		free(pipex->cmd2[i++]);
	free(pipex->cmd2);
	close(pipex->fd_out);
}

void	ft_simulate_pipex(t_pipex *pipex)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error: Pipe failed\n", 2);
		ft_free_all(pipex);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		ft_free_all(pipex);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		ft_first_child(pipex, fd);
	else
		ft_second_shild(pipex, fd, pid);
	(ft_free_all(pipex), close(fd[0]), close(fd[1]));
}

void	ft_add_slash(char **path)
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

void	ft_get_path(t_pipex *pipex, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pipex->env_path = ft_split(env[i] + 5, ':');
			ft_add_slash(pipex->env_path);
			return ;
		}
		i++;
	}
	ft_putstr_fd("Error: Cant find PATH\n", 2);
	i = 0;
	while (pipex->cmd1[i])
		free(pipex->cmd1[i++]);
	free(pipex->cmd1);
	i = 0;
	while (pipex->cmd2[i])
		free(pipex->cmd2[i++]);
	free(pipex->cmd2);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_init_struct(&pipex);
	if (ft_init_cmds(&pipex, av, env) == -1)
	{
		ft_putstr_fd("Error: Malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_simulate_pipex(&pipex);
	while (wait(NULL) > 0)
		;
	return (0);
}
