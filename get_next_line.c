/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 10:58:05 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/19 14:01:37 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	handlecharsleft(char **line, char **left)
{
	char	*charsleft;
	char	*tmp;
	int		i;

	charsleft = *left;
	if ((i = endofline(charsleft, ft_strlen(charsleft))) != -1)
	{
		*line = ft_substr(charsleft, 0, i);
		tmp = charsleft;
		if (i < ft_strlen(charsleft)
			&& !(*left = ft_substr(charsleft, i + 1, ft_strlen(charsleft) - i)))
			return (-1);
		if (tmp)
		{
			free(tmp);
			return (1);
		}
	}
	else
	{
		*line = ft_substr(charsleft, 0, ft_strlen(charsleft));
		free(charsleft);
		*left = 0;
	}
	return (0);
}

int	readloop(int fd, int *rd, char *buff, char **line)
{
	int i;

	while ((i = endofline(buff, BUFFER_SIZE)) == -1 && *rd == BUFFER_SIZE)
	{
		if (!allocandconcat(line, buff, *rd))
		{
			free(buff);
			return (-1);
		}
		i = -1;
		while (++i < BUFFER_SIZE)
			buff[i] = 0;
		if ((*rd = read(fd, buff, BUFFER_SIZE)) == -1)
		{
			free(buff);
			return (-1);
		}
	}
	return (i);
}

int	get_next_line(int fd, char **line)
{
	static char	*charsleft;
	char		*buff;
	int			i;
	int			rd;

	*line = 0;
	if (charsleft && (i = handlecharsleft(line, &charsleft)))
		return (1);
	if (!(buff = ft_calloc(1, BUFFER_SIZE * sizeof(char))))
		return (-1);
	if ((rd = read(fd, buff, BUFFER_SIZE)) == -1)
		return (-1);
	if (rd == 0)
	{
		free(buff);
		return (*line ? 1 : 0);
	}
	if ((i = readloop(fd, &rd, buff, line)) == -1)
		return (-1);
	allocandconcat(line, buff, i);
	if (i != BUFFER_SIZE)
		charsleft = (rd == i ? 0 : ft_substr(buff, i + 1, BUFFER_SIZE - i - 1));
	free(buff);
	return (1);
}
