/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:30:21 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/17 10:49:03 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

# define BACKUP_ENV_PATH "/Users/zouddach/.npm-global/bin/:/usr/local/bin/:\
/usr/bin/:/bin/:/usr/sbin/:/sbin/:/usr/local/munki/:/Library/Apple/usr/bin/:\
/Users/zouddach/.npm-global/bin/"

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	**env_path;
	char	*infile;
	char	*outfile;
	int		fd_out;
}				t_pipex;

size_t	ft_strlen(char *str);
int		ft_strncmp(char *str1, char *str2, size_t n);
int		ft_init_cmds(t_pipex *pipex, char **argv, char **env);
int		ft_have_slash(char **cmd);
void	ft_putstr_fd(char *s, int fd);
void	ft_second_shild(t_pipex *pipex, int *fd, pid_t pid);
void	ft_first_child(t_pipex *pipex, int *fd);
void	ft_get_path(t_pipex *pipex, char **env);
void	ft_free_all(t_pipex *pipex);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_init_struct(t_pipex *pipex);

#endif 