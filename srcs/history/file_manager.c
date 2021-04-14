/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:34:08 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/14 18:28:36 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*read_file(char *file)
{
	int			ret;
	t_history	*history;
	char		*line;
	
	if (!(history = malloc(sizeof(t_history))))
	{
		//msg erreur ?
		return (NULL);
	}
	if ((history->fd = open(file, O_RDONLY | O_TRUNC | O_CREAT, S_IRWXU)) < 0)
	{
		//msg erreur ?
		return (NULL);
	}
	while ((ret = get_next_line(history->fd, &line)) == 1)
		ft_lstadd_front(&history->cmds, ft_lstnew(line));
	close(history->fd);
	if (ret == -1)
	{
		//msg erreur ?
		return (NULL);
	}
	return (history);
}

int		save_command(char *command, t_history *history)
{
	if ((history->fd = open(FILE_HISTORY_NAME, O_APPEND, S_IRWXU)) < 0)
	{
		//msg erreur ?
		return (0);
	}
	ft_lstadd_front(&history->cmds, ft_lstnew(command));
	write(history->fd, command, ft_strlen(command));
	write(history->fd, "\n", 1);
	close(history->fd);
	return (1);
}
