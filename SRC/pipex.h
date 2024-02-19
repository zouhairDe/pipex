/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:48:59 by zouddach          #+#    #+#             */
/*   Updated: 2024/02/19 20:48:11 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_pipex
{
    char	**cmd1;
    char	**cmd2;
    char	*cmd1_output;
    char	*cmd2_output;
	char	**env_path;
    char	*infile;
    char	*outfile;
}                t_pipex;

// int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	**ft_split(char *str, char c);
// size_t	ft_strlen(const char *str);
// char	*ft_strdup(const char *str);
// char	*ft_strjoin(char const *s1, char const *s2);

#endif