/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:27:09 by zouddach          #+#    #+#             */
/*   Updated: 2024/02/19 21:02:56 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_it(t_pipex *pipex)
{
	int		fd[2];
	int	pid;

	pipe(fd);
	// if (access(pipex->infile, F_OK) == -1)
	// {
	//  ft_putstr_fd("Error: File does not exist\n", 2);
	// 	return ;
	// }
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(open(pipex->infile, O_RDONLY), 0);
		close(fd[1]);
		execve("/bin/cat", pipex->cmd1, NULL);
	}
	else if (pid < 0)
	{
		// ft_putstr_fd("Error: Fork failed\n", 2);
		return ;
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], 0);
		dup2(open(pipex->outfile, O_WRONLY), 1);
		close(fd[0]);
		execve("/usr/bin/wc", pipex->cmd2, NULL);
	}

}

int main(int ac, char **av/*, char **env*/)
{
	t_pipex pipex;

	if (ac != 5)
	{
		// ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (0);
	}
	pipex.cmd1 = ft_split(av[2], ' ');
	pipex.cmd2 = ft_split(av[3], ' ');
	pipex.infile = av[1];
	pipex.outfile = av[4];
	exec_it(&pipex);



	/*---- DEBBUGING ----*/
	// printf("cmd1: %s\n", pipex.cmd1[0]);
	// for (int i = 0; pipex.cmd2[i]; i++)
	// {
	// 	printf("cmd2[%d]: %s\n", i, pipex.cmd2[i]);
	// }
}