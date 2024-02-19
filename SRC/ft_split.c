/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:21:18 by zouddach          #+#    #+#             */
/*   Updated: 2024/02/19 20:30:54 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int checksep(char c)
{
    if (c == ' ' || c == '\n' || c == '\t')
        return (1);
    return (0);
}

int countWords(char *str)
{
    int count = 0;
    while (*str)
    {
        while (*str && checksep(*str))
            str++;
        if (*str)
            count++;
        while (*str && !checksep(*str))
            str++;
    }
    return (count);
}

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i] && !checksep(str[i]))
        i++;
    return (i);
}

char *allocatedWords(char *str)
{
    int i = 0;
    char *word = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (word == NULL)
        return (NULL);
    while (str[i] && !checksep(str[i]))
    {
        word[i] = str[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

char **ft_split(char *str)
{
    char **words = (char **)malloc(sizeof(char *) * (countWords(str) + 1));
    if (words == NULL)
        return (NULL);
    int i = 0;
    while(*str)
    {
        while (*str && checksep(*str))
            str++;
        if (*str && !checksep(*str))
        {
            words[i] = allocatedWords(str);
            i++;
        }
        while (*str && !checksep(*str))
            str++;
    }
    words[i] = NULL;
    return (words);
}

// int main()
// {
//     char **arr;
//     char phrase[] = "   Hello,  guys!  how are you?";
//     arr = ft_split(phrase);
//     for (int i = 0; arr[i] != NULL; i++)
//     {
//         printf("%s\n", arr[i]);
//         free(arr[i]);
//     }
//     free(arr);
//     return 0;
// }