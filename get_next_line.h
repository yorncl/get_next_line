/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:57:28 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/26 18:12:32 by mclaudel         ###   ########.fr       */
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

#include <string.h>
typedef struct	s_list
{
	int				fd;
	char			*charsleft;
	int				size;
	struct s_list	*next;
}				t_list;

/*
**	get_next_line.c
*/
int		get_next_line(int fd, char **line);
int		endofline(char *str, int len);
char	*init_buff(void);

/*
**	get_next_line_utils.c
*/
int		ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
t_list	*ft_lstnew(int fd);
t_list	*ft_lst_by_fd(int fd, t_list **list);

#endif
