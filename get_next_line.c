/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 10:58:05 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/29 16:58:49 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memjoin(char const *s1, int l1, char const *s2, int l2)
{
	char	*str;
	char	*ptr;

	if (!(str = ft_calloc(1, l1 + l2 + 1)))
		return (0);
	ptr = str;
	if (l1)
		while (l1--)
			*ptr++ = *s1++;
	if (l2)
		while (l2--)
			*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

int		managecharsleft(t_list *l, t_line *s_line)
{
	char	*tmp;
	int		eol;

	if (l->charsleft == 0)
		return (0);
	if ((eol = endofline(l->charsleft, l->size)) != -1)
	{
		if (!(*(s_line->line) = ft_substr(l->charsleft, 0, eol)))
			return (-1);
		tmp = l->charsleft;
		l->charsleft = l->size == 1 ? 0 :
			ft_substr(l->charsleft, eol + 1, l->size - eol);
		free(tmp);
		l->size -= eol + 1;
		return (1);
	}
	else
	{
		*(s_line->line) = l->charsleft;
		l->charsleft = 0;
		s_line->size = l->size;
		l->size = 0;
		return (0);
	}
}

int		allocandconcat(t_line *s_line, char *buff, int tocpy)
{
	char *tmp;

	tmp = *(s_line->line);
	*(s_line->line) = ft_memjoin(*(s_line->line), s_line->size, buff, tocpy);
	s_line->size += tocpy;
	free(tmp);
	return (0);
}

int		readloop(int fd, char *buff, t_line *s_line, t_list *current)
{
	int rd;
	int eol;
	int i;

	while ((rd = read(fd, buff, BUFFER_SIZE)) > 0 &&
		(eol = endofline(buff, rd)) == -1)
	{
		allocandconcat(s_line, buff, rd);
		i = -1;
		while (++i < BUFFER_SIZE)
			buff[i] = 0;
	}
	if (rd == -1)
		return (-1);
	if ((rd == 0 && *(s_line->line) == 0) || (rd == 0 && eol == -1))
		return (0);
	allocandconcat(s_line, buff, eol);
	current->charsleft = eol + 1 == rd ? 0 :
		ft_substr(buff, eol + 1, rd - eol - 1);
	current->size = rd - eol - 1;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*list;
	t_list			*current;
	t_line			s_line;
	char			*buff;
	int				i;

	i = 0;
	*line = 0;
	s_line = (t_line) {.size = 0, .line = line};
	if (!(current = ft_lst_by_fd(fd, &list)))
		return (-1);
	if ((i = managecharsleft(current, &s_line)) == 1)
		return (1);
	if (i == -1)
		return (-1);
	buff = ft_calloc(1, sizeof(char) * BUFFER_SIZE);
	i = readloop(fd, buff, &s_line, current);
//	if (i == 0)
//		ft_lst_remove();
	free(buff);
	return (i);
}
