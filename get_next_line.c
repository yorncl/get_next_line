/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:58:23 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/16 19:49:35 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>


int		ft_strlen(const char *s)
{
	int l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *dest;
	size_t i;

	if (!(dest = (malloc(len + 1))))
		return (0);
	i = -1;
	while (s[++i] && i < len)
		dest[i] = s[start + i];
	dest[len] = '\0';
	return (dest);
}

char *init_buff()
{
	char *buff;
	int i;

	if (!(buff = malloc(BUFFER_SIZE * sizeof(char))))
		return (0);
	i = -1;
	while(++i < BUFFER_SIZE)
		buff[i] = 0;
	return (buff);
}

int endofline(char *str)
{
	int i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}


int	allocandconcat(char **line, char *buff, int tocpy)
{
	char *tmp;
	int i;
	int l;

	l = (*line ? ft_strlen(*line) : 0);
	if (!(tmp = malloc((l + tocpy + 1) * sizeof(char))))
		return (0);
	tmp[l + tocpy] = '\0';
	i = -1;
	while (++i < l)
		tmp[i] = (*line)[i];
	i = -1;
	while (++i < tocpy)
		tmp[l + i] = buff[i];
	printf("%d \n", tocpy);
	if (*line)
		free(*line);
	*line = tmp;
	i = -1;
	return (1);
}


// handlecharsleft()
// {

// }


int get_next_line(int fd, char **line)
{
	static char *charsleft;
	char *buff;
	char *tmp;
	int i;
	int rd;

	*line = 0;
	if (charsleft)
	{
		if ((i = endofline(charsleft)) != -1)
		{
			*line = ft_substr(charsleft, 0, i);
			tmp = charsleft;
			if(i < ft_strlen(charsleft))
				charsleft = ft_substr(charsleft, i + 1, ft_strlen(charsleft) - i);
			if (tmp)
			{
				free (tmp);
				return (1);
			}
		}
		else
		{
			*line = ft_substr(charsleft, 0, ft_strlen(charsleft));
			free(charsleft);
			charsleft = 0;
		}
	}
	
	//TO PROTECC
	buff = init_buff();

	if ((rd = read(fd, buff, BUFFER_SIZE)) == -1)
		return (-1);
	if (rd == 0)
	{
		free(buff);
	 	return (*line ? 1 : 0);
	}
	while ((i = endofline(buff)) == -1 && rd == BUFFER_SIZE)
	{
		if(!allocandconcat(line,buff, rd))
		{
			free(buff);
			return (-1);
		}
		i = -1;
		while (++i < BUFFER_SIZE)
			buff[i] = 0;
		if((rd = read(fd, buff, BUFFER_SIZE)) == -1)
		{
			free(buff);
			return (-1);
		}
	}
	allocandconcat(line, buff, i);
	if (i != BUFFER_SIZE)
		charsleft = ft_substr(buff, i + 1, BUFFER_SIZE - i);
	free(buff);
	return (1);
}