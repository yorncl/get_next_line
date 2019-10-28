/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 10:58:05 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/26 18:54:09 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		managecharsleft(t_list *l, t_line *s_line)
{
	char *tmp;
	int	eol;

	if (l->charsleft == 0)
		return (0);
	if ((eol = endofline(l->charsleft, l->size)) != -1) 	//SI FIN DE LIGNE
	{
		if (eol == 0 && !(*(s_line->line) = ft_calloc(1, 1))) // si le \n est le premier charactere
			return (-1);
		else if (!(*(s_line->line) = ft_substr(l->charsleft, 0, eol))) // on ne rajoute pas le + 1 pour ne pas inclure le \n dans line
			return (-1);
		tmp = l->charsleft;
		l->charsleft = l->size == 1 ? 0 :
			ft_substr(l->charsleft, eol + 1, l->size - eol); // CHECK ERROR CHECK ERROR CHECK ERROR CHECK ERROR
		free(tmp);
		l->size -= eol + 1;
		return (1);	//one line read
	}
	else{
		*(s_line->line) = l->charsleft; // no need to free
		l->charsleft = 0;
		s_line->size = l->size;
		l->size = 0;
		return (0); // No line read
	}
}


int	readloop(int fd, char *buff, t_line	*s_line, t_list *current)
{
	char *tmp;
	int rd;
	int eol;
	int i;

	while ((rd  = read(fd, buff, BUFFER_SIZE)) > 0 && (eol = endofline(buff, rd)) == -1)
	{
		tmp = *(s_line->line);
		*(s_line->line) = ft_memjoin(*(s_line->line), s_line->size, buff, rd); // TO PROTECC
		s_line->size += rd;
		free(tmp);
		i = -1;
		while(++i < BUFFER_SIZE)
			buff[i] = 0;
	}
	if (rd == -1)
		return (-1);
	if (rd == 0 && *(s_line->line) == 0) // Fin de fichier sans aucun byte lu
			return (0);
	if (rd == 0 && eol == -1) // If nothing else to read and still no end of line
		return (0);
	tmp = *(s_line->line);
	*(s_line->line) = ft_memjoin(*(s_line->line), s_line->size, buff, eol); // TO PROTECC on ne met pas de + 1 pour ne pas inclure le \n
	s_line->size += eol;
	free(tmp);
	current->charsleft = eol + 1 == rd ? 0 : ft_substr(buff, eol + 1, rd - eol - 1); // on met +1 pour ne pas inclure le \n
	current->size = rd - eol - 1;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static t_list	*list;
	t_list			*current;
	t_line			s_line;
	char			*buff;
	int				i;

	i = 0;
	*line = 0;
	s_line = (t_line) {.size = 0, .line = line};
	if(!(current = ft_lst_by_fd(fd, &list)))
		return (-1);
	if ((i = managecharsleft(current, &s_line)) == 1)
		return (1);
	if (i == -1)
		return (-1);
	buff = ft_calloc(1, sizeof(char) * BUFFER_SIZE);
	i = readloop(fd, buff, &s_line, current);
	free(buff);
	return (i);
}
