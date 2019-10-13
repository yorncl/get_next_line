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

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!(dest = (malloc(len + 1))))
		return (0);
	i = -1;
	if (start < ft_strlen(s))
		while (s[++i] && i < len)
			dest[i] = s[start + i];
		dest[len] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	int l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}


char *init_buff()
{
	char *buff;

	if (!(buff = malloc(BUFF_SIZE * sizeof(char))))
		return (0);
	return (buff);	
}

int endofline(char *str)
{
	int i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] =='\n')
	return (str[i] == 'EOF' ? i : -1);
}

int get_next_line(int fd, char **line)
{
	static char *left;
	char *buff;
	int l;
	int rd;

	l = -1;
	buff = init_buff();
	if ((rd = read(fd, buff, BUFF_SIZE)))
		return (0);
	if (rd < BUFF_SIZE)
	{
		
	}
	free(buff);
}