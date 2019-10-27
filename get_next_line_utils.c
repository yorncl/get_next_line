/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:58:25 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/26 18:51:03 by mclaudel         ###   ########.fr       */
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

char	*ft_memjoin(char const *s1, size_t l1, char const *s2, size_t l2)
{
	char	*str;
	char	*ptr;

	if (!(str = ft_calloc(1, l1 + l2)))
		return (0);
	ptr = str;
	while (l1--)
		*ptr++ = *s1++;
	while (l2--)
		*ptr++ = *s2++;
	return (str);
}


t_list	*ft_lstnew(int fd)
{
	t_list *el;

	if (!(el = ft_calloc(1, sizeof(t_list))))
		return (NULL);
	el->fd = fd;
	el->charsleft = 0;
	el->size = 0;
	el->next = 0;
	return (el);
}

t_list	*ft_lst_by_fd(int fd, t_list **list)
{
	t_list *prev;
	t_list *l;

	if (!*list)
	{
		*list = ft_lstnew(fd);
		return (*list);
	}
	l = *list;
	while (l)
		if (fd == l->fd)
			return (l);
		else
		{
			prev = l;
			l = l->next;
		}
	prev->next = ft_lstnew(fd);
	return (prev->next);
}
