/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:57:28 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/26 17:49:28 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

/*
**	get_next_line.c
*/
int		get_next_line(int fd, char **line);
int		endofline(char *str, int len);
int		allocandconcat(char **line, char *buff, int tocpy);
int		handlecharsleft(char **line, char **left);
char	*init_buff(void);

/*
**	get_next_line_utils.c
*/
int		ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);


typedef struct	s_list
{
	int				fd;
	char			*charsleft;
	int				size;
	struct s_list	*next;
}				t_list;
#endif
