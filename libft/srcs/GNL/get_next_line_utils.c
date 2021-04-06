/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:45:09 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/18 16:28:57 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/libft.h"

size_t	line_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != 10)
		i++;
	return (i);
}

t_file	*gnl_lstnew(int fd)
{
	t_file	*new;

	if (!(new = malloc(sizeof(t_file))))
		return (0);
	new->next = 0;
	new->fd = fd;
	new->buff[0] = 0;
	return (new);
}

t_file	*get_lstelem(t_file **root, int fd)
{
	t_file	*elem;

	if (fd < 0)
		return (0);
	if (!(*root))
	{
		if (!(elem = gnl_lstnew(fd)))
			return (0);
		*root = elem;
		return (elem);
	}
	elem = *root;
	while (elem->next && elem->fd != fd)
		elem = elem->next;
	if (elem->fd == fd)
		return (elem);
	return (elem->next = gnl_lstnew(fd));
}

void	ft_lstremove(t_file **root, int fd)
{
	t_file	*element;
	t_file	*temp;

	while (*root && (*root)->fd == fd)
	{
		temp = *root;
		*root = (*root)->next;
		free(temp);
	}
	element = *root;
	while (element && element->next)
	{
		if (element->next->fd == fd)
		{
			temp = element->next;
			element->next = element->next->next;
			free(temp);
		}
		element = element->next;
	}
}
