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



int		managecharsleft(t_list *l, char **line)
{
	char *tmp;
	int	eol;

	if (l->charsleft == 0)
		return (0);
	if ((eol = endofline(l->charsleft, l->size)) != -1) 	//SI FIN DE LIGNE
	{
		if (eol == 0 && !(*line = ft_calloc(1, 1))) // si le \n est le premier charactere
			return (-1);
		else if (!(*line = ft_substr(l->charsleft, 0, eol))) // on ne rajoute pas le + 1 pour ne pas inclure le \n dans line
			return (-1);
		tmp = l->charsleft;
		l->charsleft = l->size == 1 ? 0 :
			ft_substr(l->charsleft, eol + 1, l->size - eol); // CHECK ERROR CHECK ERROR CHECK ERROR CHECK ERROR
		free(tmp);
		l->size -= eol + 1;
		return (0);
	}
	else{
		*line = l->charsleft; // no need to free
		l->charsleft = 0;
		eol = l->size;
		l->size = 0;
		return (eol); // Return the length of the string just read
	}
}


int	get_next_line(int fd, char **line)
{
	static t_list	*list;
	t_list			*current;
	char			*buff;
	int				rd;
	int				i;

	(void) current;	
	(void)	buff;
	rd = 0;
	//ERREUR MAILLON
	if(!(current = ft_lst_by_fd(fd, &list)))
		return (-1);
	//CE QUI RESTE
	current->charsleft = strdup("1\n2\n3");
	current->size = ft_strlen("1\n2\n3");
	if ((i = managecharsleft(current, line)) == 0)
		return (1);
	if (i == -1)
		return (-1);
	//LECTURE DU FICHIER SI BESOIN

	buff = ft_calloc(1, sizeof(char) * BUFFER_SIZE);
	while ((rd  = read(fd, buff, BUFFER_SIZE)) > 0 && endofline(buff, BUFFER_SIZE) == -1)
	{
		memjoin(line, i, buff, BUFFER_SIZE);
	}
	if (rd == -1)
	//if (charsleft())
	//	return (0);
	*line = 0;
	return (rd == 0 ? 0 : 1);
}
