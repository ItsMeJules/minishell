/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:19:32 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/14 16:24:40 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cursor_move(int mode, char *input)
{
	if (mode == LEFT_ARROW_KEY && g_tc.curr_col > g_tc.col)
		move_cursor(g_tc.curr_row, --g_tc.curr_col);
	else if (mode == RIGHT_ARROW_KEY
			&& g_tc.curr_col < g_tc.col + (int)ft_strlen(input))
		move_cursor(g_tc.curr_row, ++g_tc.curr_col);
}
