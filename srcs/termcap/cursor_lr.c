/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_lr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:40:01 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/20 17:08:54 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cursor_move_left()
{
	if (g_tc.curr_row == g_tc.row)
	{
		if (g_tc.curr_col <= g_tc.col)
			return ;
	}
	else if (g_tc.curr_col == 0)
	{
		move_cursor(g_tc.curr_row - 1, g_tc.w.ws_col - 1);
		return ;
	}
	move_cursor(g_tc.curr_row, g_tc.curr_col - 1);
}

void	handle_cursor_move_right(char **input)
{
	int	max_rel_input_pos;
	int	rel_row = g_tc.curr_row == g_tc.row ? 1  : g_tc.curr_row - g_tc.row;

	if (input && *input)
	{
		max_rel_input_pos = g_tc.w.ws_col * (rel_row) - g_tc.curr_col;
		printf("%d %d %d\n", max_rel_input_pos, g_tc.curr_row, g_tc.row);
		if (g_tc.curr_row == g_tc.row)
		{
			if (g_tc.col + (int)ft_strlen(*input) > g_tc.w.ws_col
					&& g_tc.curr_col + 1 == g_tc.w.ws_col)
				move_cursor(g_tc.curr_row + 1, 0);
		}
		else if (g_tc.curr_col == g_tc.w.ws_col)
		{
			move_cursor(g_tc.curr_row + 1, 0);
			return ;
		}
		else if (max_rel_input_pos == (int)ft_strlen(*input))
			return ;
		move_cursor(g_tc.curr_row, g_tc.curr_col + 1);
	}
}
