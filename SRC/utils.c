/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:02:50 by zouddach          #+#    #+#             */
/*   Updated: 2024/02/21 17:16:22 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
	return ;
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = -1;
	if (s && fd >= 0)
	{
		while (s[++i])
			ft_putchar_fd(s[i], fd);
	}
	return ;
}

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i] || !str1[i] || !str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		lens1;
	int		lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	dest = (char *)malloc(lens1 + lens2 + 1);
	if (!dest)
		return (NULL);
	while (*s1 && lens1 > 0)
	{
		*dest = *s1;
		dest++;
		s1++;
	}
	while (*s2 && lens2 > 0)
	{
		*dest = *s2;
		dest++;
		s2++;
	}
	*dest = '\0';
	free(s1 - lens1);
	return (dest - lens1 - lens2);
}