/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:26:13 by tvachera          #+#    #+#             */
/*   Updated: 2020/12/18 20:02:16 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/libft.h"

int		get_line_from_buff(char **line, t_file *elem)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(line[0] = malloc(sizeof(char) * (line_len(elem->buff) + 1))))
		return (-1);
	while (elem->buff[i] && elem->buff[i] != 10)
	{
		line[0][i] = elem->buff[i];
		i++;
	}
	line[0][i] = 0;
	if (elem->buff[i] == 10)
		i++;
	while (elem->buff[i])
	{
		elem->buff[j] = elem->buff[i];
		i++;
		j++;
	}
	elem->buff[j] = 0;
	return (1);
}

char	*concat(char *ret, t_file *elem, ssize_t bytes)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(line = malloc(sizeof(char) * (ft_strlen(ret)
		+ line_len(elem->buff) + 1))))
		return (0);
	while (ret[i])
	{
		line[i] = ret[i];
		i++;
	}
	while (elem->buff[j] != 10 && j < bytes)
	{
		line[i] = elem->buff[j];
		i++;
		j++;
	}
	line[i] = 0;
	free(ret);
	return (line);
}

int		manage_exit(t_file **root, t_file *elem, int bytes, char **line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (bytes == 0)
	{
		ft_lstremove(root, elem->fd);
		free(line[0]);
		return (0);
	}
	while (i < bytes && elem->buff[i] != 10)
		i++;
	i++;
	while (i < bytes)
	{
		elem->buff[j] = elem->buff[i];
		i++;
		j++;
	}
	elem->buff[j] = 0;
	return (1);
}

bool	find_endl(char *buff, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (buff[i] == 10)
			return (true);
		i++;
	}
	return (false);
}

int		get_next_line(int fd, char **line)
{
	static t_file	*root = 0;
	char			*ret;
	ssize_t			bytes;
	t_file			*elem;

	ret = 0;
	bytes = 0;
	if (!line || BUFFER_SIZE <= 0 || !(elem = get_lstelem(&root, fd)))
		return (-1);
	if (ft_strlen(elem->buff) > line_len(elem->buff))
		return (get_line_from_buff(line, elem));
	if (get_line_from_buff(&ret, elem) == -1)
		return (-1);
	while (find_endl(elem->buff, bytes) == false)
	{
		if (!(bytes = read(fd, elem->buff, BUFFER_SIZE)))
			break ;
		if (bytes < 0 || !(ret = concat(ret, elem, bytes)))
		{
			free(ret);
			return (-1);
		}
	}
	line[0] = ret;
	return (manage_exit(&root, elem, bytes, line));
}
