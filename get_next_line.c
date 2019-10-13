/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:58:23 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/13 18:28:39 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

// char *ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char *dest;
// 	size_t i;

// 	if (!(dest = (malloc(len + 1))))
// 		return (0);
// 	i = -1;
// 	while (s[++i] && i < len)
// 		dest[i] = s[start + i];
// 	dest[len] = '\0';
// 	return (dest);
// }

// char *init_buff()
// {
// 	char *buff;

// 	if (!(buff = malloc(BUFF_SIZE * sizeof(char))))
// 		return (0);
// 	return (buff);
// }

// int endofline(char *str)
// {
// 	int i;

// 	if (!str)
// 		return (-1);
// 	i = -1;
// 	while (str[++i])
// 		if (str[i] == '\n')
// 			return (i);
// 	return (i);
// }

// int get_next_line(int fd, char **line)
// {
// 	static char *left;
// 	char *buff;
// 	int i;
// 	int rd;

// 	buff = init_buff();

// 	if (left)
// 	{
// 		if ((i = endofline(left)) != -1)
// 		{
// 			*line = ft_substr(left, 0, i);
// 			if(i < BUFFER_SIZE)
					
// 		}
// 		else
// 		{

// 		}
// 	}
// 	free(buff);
// }

#include <stdio.h>
#include <unistd.h>
int main()
{
	char test[50];

	int fd = open("testfile", O_RDONLY);
	read(fd,buff,50);
	printf("%s", buff);
}