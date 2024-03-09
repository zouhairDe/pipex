/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pipex.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: zouddach <zouddach@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/01/24 23:48:59 by zouddach		  #+#	#+#			 */
/*   Updated: 2024/02/24 21:31:11 by zouddach		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	**env_path;
	int		path_length;
	char	*infile;
	char	*outfile;
}				t_pipex;

int		ft_strncmp(char *str1, char *str2, size_t n);
char	**ft_split(char *str, char c);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
void	second_shild(t_pipex *pipex, int *fd, pid_t pid);
void	first_child(t_pipex *pipex, int *fd);
void	get_backupenv(t_pipex *pipex);
void	get_path(t_pipex *pipex, char **env);
void	ft_free_all(t_pipex *pipex);

#endif