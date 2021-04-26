/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:04:22 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/26 19:51:01 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_after(int row, int col)
{
	move_cursor(row, col);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
}

void	move_cursor(int row, int col)
{
	tputs(tgoto(tgetstr("cm", NULL), col, row), 1, ft_putchar);
	g_tc.curr_row = row;
	g_tc.curr_col = col;
}
