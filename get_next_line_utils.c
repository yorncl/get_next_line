/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:58:25 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/26 17:23:23 by mclaudel         ###   ########.fr       */
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
	while (++i < len && str[i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*ptr;
	size_t	l1;
	size_t	l2;

	l1 = s1 ? ft_strlen(s1) : 0;
	l2 = s2 ? ft_strlen(s2) : 0;
	if (!(str = ft_calloc(1, l1 + l2 + 1)))
		return (0);
	ptr = str;
	while (s1 && *s1)
		*ptr++ = *s1++;
	while (s2 && *s2)
		*ptr++ = *s2++;
	return (str);
}
