/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:04:22 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/20 14:31:52 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_after(int row)
{
	move_cursor(row, 0);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
}

void	move_cursor(int row, int col)
{
	tputs(tgoto(tgetstr("cm", NULL), col, row), 1, ft_putchar);
	g_tc.curr_row = row;
	g_tc.curr_col = col;
}
