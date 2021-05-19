/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:34:08 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/19 14:31:24 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*read_file(char *file)
{
	int			ret;
	t_history	*history;
	char		*line;

	history = malloc(sizeof(t_history));
	if (!history)
		return (NULL);
	history->fd = open(file, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (history->fd < 0)
		return (NULL);
	history->size = 0;
	history->cmds = NULL;
	ret = get_next_line(history->fd, &line);
	while (ret == 1)
	{
		ft_lstadd_front(&history->cmds, ft_lstnew(line));
		history->size++;
		ret = get_next_line(history->fd, &line);
	}
	close(history->fd);
	history->pos = -1;
	history->fd = -1;
	if (ret == -1)
		return (NULL);
	return (history);
}

int	save_command(char *command, t_history *history)
{
	if (command == NULL
		|| (history->cmds && ft_strcmp(command, history->cmds->content) == 0))
		return (0);
	history->fd = open(FILE_HISTORY_NAME, O_APPEND | O_WRONLY);
	if (history->fd < 0)
		return (0);
	history->size++;
	ft_lstadd_front(&history->cmds, ft_lstnew(ft_strdup(command)));
	write(history->fd, command, ft_strlen(command));
	write(history->fd, "\n", 1);
	close(history->fd);
	return (1);
}

void	free_history(t_history *history)
{
	ft_lstclear(&history->cmds, free);
	free(history);
}
