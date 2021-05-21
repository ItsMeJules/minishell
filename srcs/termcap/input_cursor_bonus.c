/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cursor_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:25:28 by jules             #+#    #+#             */
/*   Updated: 2021/05/21 13:48:00 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_home(void)
{
	move_cursor(g_tc.row, g_tc.col);
	g_tc.cursor_pos = 0;
}

void	handle_end(char **input)
{
	int	len;
	int	ratio;

	if (!input || !*input)
		return ;
	len = ft_strlen(*input) + g_tc.col;
	ratio = (int)(len / g_tc.w.ws_col);
	g_tc.cursor_pos = len - g_tc.col;
	if (g_tc.row + ratio >= g_tc.w.ws_row)
		g_tc.row -= g_tc.row + ratio - g_tc.w.ws_row + 1;
	g_tc.curr_row = g_tc.row + ratio;
	g_tc.curr_col = len;
	if (len > g_tc.w.ws_col)
		g_tc.curr_col = len % g_tc.w.ws_col;
	move_cursor(g_tc.curr_row, g_tc.curr_col);
}

void	handle_move_line(int up, char **input)
{
	int	nb_lines;
	int	len;

	if (up)
	{
		if (g_tc.curr_row == g_tc.row)
			return ;
		if (g_tc.curr_row - 1 == g_tc.row && g_tc.curr_col < g_tc.col)
			return (handle_home());
		g_tc.cursor_pos -= g_tc.w.ws_col;
		move_cursor(g_tc.curr_row - 1, g_tc.curr_col);
	}
	else
	{
		len = ft_strlen(*input);
		nb_lines = (int)((len + g_tc.col) / g_tc.w.ws_col);
		if (g_tc.curr_row == g_tc.row + nb_lines)
			return ;
		if (g_tc.curr_row + 1 == g_tc.row + nb_lines && g_tc.curr_col
			> (len + g_tc.col) % g_tc.w.ws_col)
			return (handle_end(input));
		g_tc.cursor_pos += g_tc.w.ws_col;
		move_cursor(g_tc.curr_row + 1, g_tc.curr_col);
	}
}
