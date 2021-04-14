/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:19:32 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/14 15:21:37 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	handle_cursor_move(int mode)
{
	if (mode == LEFT_ARROW_KEY)
		move_cursor(g_tc.curr_row, g_tc.curr_col--);
	else if (mode == RIGHT_ARROW_KEY)
		move_cursor(g_tc.curr_row--, g_tc.curr_col);
}
