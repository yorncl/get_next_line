/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:58:23 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/17 13:39:04 by mclaudel         ###   ########.fr       */
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

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char *ptr;
	int len;
	int i ;

	len = count * size;
	if (!(ptr = malloc(len)))
		return (0);
	i = -1;
	while (++i < len)
		ptr[i] = 0;
	return (ptr);
}


char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *dest;
	size_t i;

	if (!(dest = (ft_calloc(1, len + 1))))
		return (0);
	i = -1;
	while (s[++i] && i < len)
		dest[i] = s[start + i];
	return (dest);
}

char *init_buff()
{
	char *buff;

	if (!(buff = ft_calloc(1, BUFFER_SIZE * sizeof(char))))
		return (0);
	return (buff);
}

int endofline(char *str, int len)
{
	int i;

	if (!str)
		return (-1);
	i = -1;
	while (++i < len)
		if (str[i] == '\n' || str[i] == '\0')
			return (i);
	return (-1);
}


int	allocandconcat(char **line, char *buff, int tocpy)
{
	char *tmp;
	int i;
	int l;

	l = (*line ? ft_strlen(*line) : 0);
	if (!(tmp = ft_calloc(1,(l + tocpy + 1) * sizeof(char))))
		return (0);
	i = -1;
	while (++i < l)
		tmp[i] = (*line)[i];
	i = -1;
	while (++i < tocpy)
		tmp[l + i] = buff[i];
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
		if ((i = endofline(charsleft, ft_strlen(charsleft))) != -1)
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
	while ((i = endofline(buff, BUFFER_SIZE)) == -1 && rd == BUFFER_SIZE)
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
		charsleft = ft_substr(buff, i + 1, BUFFER_SIZE - i - 1);
	free(buff);
	return (1);
}