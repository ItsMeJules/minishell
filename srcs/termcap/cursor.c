/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:19:32 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/15 15:18:41 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cursor_move(int mode, char **input, t_history *history)
{
	if (mode == LEFT_ARROW_KEY && g_tc.curr_col > g_tc.col)
		move_cursor(g_tc.curr_row, --g_tc.curr_col);
	else if (mode == RIGHT_ARROW_KEY
			&& g_tc.curr_col < g_tc.col + (int)ft_strlen(*input))
		move_cursor(g_tc.curr_row, ++g_tc.curr_col);
	else if (mode == UP_ARROW_KEY && (size_t)history->pos + 1 < history->size)
	{
		*input = ft_strdup(ft_lstat(history->cmds, ++history->pos)->content);
		rewrite_line(*input, g_tc.col + ft_strlen(*input));
	}
	else if (mode == DOWN_ARROW_KEY && history->pos != -1)
	{
		if (history->pos - 1 < 0)
		{
			history->pos--;
			*input = NULL;
			clear_after(g_tc.row, g_tc.col);
			return ;
		}
		*input = ft_strdup(ft_lstat(history->cmds, --history->pos)->content);
		rewrite_line(*input, g_tc.col + ft_strlen(*input));
	}
}

char	*new_str(int str_size)
{
	char	*new_str;

	if (str_size == -1)
		return (NULL);
	if (!(new_str = malloc((str_size + 1) * sizeof(char))))	
	{
		//msg d'erreur ?
		return (NULL);
	}
	return (new_str);
}

void	handle_backspace(char **input)
{
	int		rel_col;
	int		i;
	int		j;
	char	*str;

	if (input == NULL)
		return ;
	str = new_str(ft_strlen(*input) - 1);
	if (!str)
		return ;
	rel_col = g_tc.curr_col - g_tc.col;
	i = -1;
	j = 0;
	while ((*input)[++i])
	{
		if (i != rel_col)
			str[i] = (*input)[j];
		j++;
	}
	str[i - 1] = 0;
	free(*input);
	*input = str;
	rewrite_line(str, --g_tc.curr_col);
}
