/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:40:01 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/19 14:17:41 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cursor_move_left(void)
{
	if (g_tc.curr_row == g_tc.row)
	{
		if (g_tc.cursor_pos == 0)
			return ;
	}
	else if (g_tc.curr_col == 0)
	{
		move_cursor(g_tc.curr_row - 1, g_tc.w.ws_col - 1);
		g_tc.cursor_pos--;
		return ;
	}
	move_cursor(g_tc.curr_row, g_tc.curr_col - 1);
	g_tc.cursor_pos--;
}

void	handle_cursor_move_right(char **input)
{
	if (!input || !*input)
		return ;
	if (g_tc.cursor_pos < (int)ft_strlen(*input))
	{
		if (g_tc.curr_col == g_tc.w.ws_col)
			move_cursor(g_tc.curr_row + 1, 1);
		else
			move_cursor(g_tc.curr_row, g_tc.curr_col + 1);
		g_tc.cursor_pos++;
	}
}

void	repos_cursor(int len, char **input)
{
	g_tc.cursor_pos = len - g_tc.col;
	if (len > g_tc.w.ws_col)
		rewrite_line(*input, len % g_tc.w.ws_col);
	else
		rewrite_line(*input, len);
}

void	handle_up_arrow(t_history *history, char **input)
{
	int	len;
	int	ratio;

	if ((size_t)history->pos + 1 < history->size)
	{
		if (*input)
			free(*input);
		*input = ft_strdup(ft_lstat(history->cmds, ++history->pos)->content);
		len = ft_strlen(*input) + g_tc.col;
		ratio = (int)(len / g_tc.w.ws_col);
		repos_cursor(len, input);
		if (g_tc.row + ratio >= g_tc.w.ws_row)
			g_tc.row -= g_tc.row + ratio - g_tc.w.ws_row + 1;
		g_tc.curr_row = g_tc.row + ratio;
		move_cursor(g_tc.curr_row, g_tc.curr_col);
	}
}

void	handle_down_arrow(t_history *history, char **input)
{
	int	ratio;

	if (history->pos == -1)
		return ;
	if (history->pos - 1 < 0)
	{
		history->pos--;
		free(*input);
		*input = NULL;
		clear_after(g_tc.row, g_tc.col);
		move_cursor(g_tc.row, g_tc.col);
		g_tc.cursor_pos = 0;
		return ;
	}
	if (*input)
		free(*input);
	*input = ft_strdup(ft_lstat(history->cmds, --history->pos)->content);
	ratio = (int)((ft_strlen(*input) + g_tc.col) / g_tc.w.ws_col);
	repos_cursor(g_tc.col + ft_strlen(*input), input);
	if (g_tc.row + ratio >= g_tc.w.ws_row)
		g_tc.row -= g_tc.row + ratio - g_tc.w.ws_row + 1;
	g_tc.curr_row = g_tc.row + ratio;
	move_cursor(g_tc.curr_row, g_tc.curr_col);
}
