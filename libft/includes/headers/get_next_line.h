/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:43:42 by tvachera          #+#    #+#             */
/*   Updated: 2020/12/18 20:02:50 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1
# define BUFFER_SIZE 4096

typedef struct		s_file
{
	int				fd;
	char			buff[BUFFER_SIZE > 0 ? BUFFER_SIZE : 1];
	struct s_file	*next;
}					t_file;

size_t				line_len(char *str);
t_file				*gnl_lstnew(int fd);
t_file				*get_lstelem(t_file **root, int fd);
void				ft_lstremove(t_file **root, int fd);
int					get_line_from_buff(char **line, t_file *elem);
char				*concat(char *ret, t_file *elem, ssize_t bytes);
int					manage_exit(t_file **root, t_file *elem, int bytes
					, char **line);
bool				find_endl(char *buff, int size);
int					get_next_line(int fd, char **line);

#endif
