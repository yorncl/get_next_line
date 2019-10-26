/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 10:58:05 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/26 17:46:52 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	handlecharsleft(char **line, char **left)
{
	char	*charsleft;
	char	*tmp;
	int		i;

	charsleft = *left;
	if (!charsleft )
	{
		free(charsleft);
		return (0);
	}
	//si on trouve une fin de ligne dans les characteres restants
	if ((i = endofline(charsleft, ft_strlen(charsleft))) != -1)
	{
		// on mets la ligne toruvee dans line
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
	// sinon on recupere les characteres restant et on met ca dans line pour continuer la lecture
	else
	{
		*line = ft_substr(charsleft, 0, ft_strlen(charsleft));
		free(charsleft);
		*left = 0;
	}
	return (0);
}

int	readline(int fd, char *buff, char **line, char **charsleft)
{
	int rd;
	int lastrd;
	int i;
	char *tmp;
	char *sub;

	// on mets lastrd a zero, de cette maniere on retroune 0 lorsque la tete de lecture est a la fin
	i = 0;
	lastrd = 0;
	// tant qu'on lit plus de zero bytes et qu'il n'y a pas d'erreur et que lq fin de lq ligne n'est pas atteinte
	while ((rd = read(fd, buff, BUFFER_SIZE)) > 0  
			&& (i = endofline(buff, BUFFER_SIZE)) == -1)
		{
			tmp = *line;
			// On concat le buffer a la ligne dans un nouveau malloc
			*line = ft_strjoin(*line ,buff);
			// On free le dernier malloc
			free(tmp);
			// On remet les bytes du buff a nuls pour éviter de se retrouver avec des restes de phrases plus tard
			i = -1;
			while (++i < BUFFER_SIZE)
				buff[i] = 0;
			lastrd = rd;
		}
		if (rd > 0)
		{
		tmp = *line;
			// On concat le buffer a la ligne dans un nouveau malloc
		sub = ft_substr(buff, 0, i);
		*line = ft_strjoin(*line , sub);
		free(tmp);
		free(sub);
		}
	// Si il y a une erreur
	if (rd == -1)
			return (-1);
	if (rd == 0) //cas ou la lecture est terminee
		*charsleft = i < lastrd - 1 ? ft_substr(buff, i + 1, lastrd - i - 1) : 0; // si on a lu aucun byte precedement alors on mets a nul
	else if (rd < BUFFER_SIZE) // cas ou on vient de lire les derniers bytes du fichier 
		*charsleft = i < rd - 1 ? ft_substr(buff, i + 1, rd - i - 1) : 0; // si l'index est au bout on met a nul
	else	// cas ou on vient de lire la taille du buffer entier
		*charsleft = i < BUFFER_SIZE - 1 ? ft_substr(buff, i + 1, BUFFER_SIZE - i - 1) : 0; // si l'index est au bout on met a nul
	// Si rd == 0 alors on est a la fin du fichier et on renvoie le nombre de bytes lus avant d'avoir atteint la fin
	return (rd == 0 ? lastrd : rd); // si on vient d'atteindre la fin du fichier mais qu'on a bien lu des bytes avant on renvoit lastrd
}


/*
**	THE get_next_line function
*/
int	get_next_line(int fd, char **line)
{
	static char	*charsleft;
	char		*buff;
	int			rd;

	*line = 0;
	// HANDLES CHARS LEFT si une ligne a ete lu on retourne 1
	if ((rd = handlecharsleft(line, &charsleft)) == -1) // si erreur
		return (-1);
	if (rd) // si une ligne a ete recuperee
		return (1);
	// si aucune ligne n'a pu etre recuperee par charsleft alors on essaye de lire le fichier
	// buff init
	if (!(buff = ft_calloc(1, (BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	// Si la lectrue de la ligne genere une erreur on free
	if ((rd = readline(fd, buff, line, &charsleft)) == -1)
	{
		free(buff);
		return (-1);
	}
	free(buff);
	// Si rd est a zero alors on est a la fin du fichier et 
	// la lecture de charsleft n'a pas trouve de \n, on renvoit donc 0
	// Sinon, rd n'est pas 
	return (rd == 0 ? 0 : 1);
}
