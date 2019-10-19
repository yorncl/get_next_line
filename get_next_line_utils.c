/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:58:25 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/19 14:01:55 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	unsigned char	*ptr;
	int				len;
	int				i;

	len = count * size;
	if (!(ptr = malloc(len)))
		return (0);
	i = -1;
	while (++i < len)
		ptr[i] = 0;
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!(dest = (ft_calloc(1, len + 1))))
		return (0);
	i = -1;
	while (s[++i] && i < len)
		dest[i] = s[start + i];
	return (dest);
}

int	endofline(char *str, int len)
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
	char	*tmp;
	int		i;
	int		l;

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
