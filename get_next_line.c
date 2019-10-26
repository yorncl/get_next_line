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

	if (!l->charsleft)
		return (0);
	//SI FIN DE LIGNE
	if ((eol = endofline(l->charsleft, l->size)) != -1)
	{
		if (eol == 0 && !(*line = ft_calloc(1, 1))) // si le \n est le premier charactere
			return (-1);
		else if (!(*line = ft_substr(l->charsleft, 0, eol))) // on ne rajoute pas le + 1 pour ne pas inclure le \n dans line
			return (-1);
		tmp = l->charsleft;
		l->charsleft = l->size == 1 ? 0 :
			ft_substr(l->charsleft, eol + 1, l->size - eol);
		free(tmp);
		l->size -= eol + 1;
	}
	else{
		*line = l->charsleft; // no need to free
		l->charsleft = 0;
		l->size = 0;
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
	if ((i = managecharsleft(current)) == 1)
		return (1);
	if (i == -1)
		return (-1);
	//LECTURE DU FICHIER SI BESOIN
	if (charsleft())
		return (0);
	printf("Maillon au fd : %d\n", current->fd);
	*line = 0;
	return (rd == 0 ? 0 : 1);
}
