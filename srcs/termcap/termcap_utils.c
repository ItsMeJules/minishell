/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:26:46 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/14 17:15:31 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_tckey(char tc[4], int const_tc)
{
	if (const_tc == LEFT_ARROW_KEY)
		return (tc[0] == 27 && (tc[1] == 79 || tc[1] == 91) && tc[2] == 68);
	else if (const_tc == UP_ARROW_KEY)
		return (tc[0] == 27 && (tc[1] == 79 || tc[1] == 91) && tc[2] == 65);
	else if (const_tc == DOWN_ARROW_KEY)
		return (tc[0] == 27 && (tc[1] == 79 || tc[1] == 91) && tc[2] == 66);
	else if (const_tc == RIGHT_ARROW_KEY)
		return (tc[0] == 27 && (tc[1] == 79 || tc[1] == 91) && tc[2] == 67);
	else if (const_tc == BACKSPACE_KEY)
		return (tc[0] == 8 || tc[0] == 127);
	return (0);
}

void	get_cursor_pos(void)
{
	char	buf[400];
	int		i;

	write(1, "\033[6n", 4);
	buf[read(1, buf, 400)] = 0;
	g_tc.col = 0;
	g_tc.row = 0;
	i = 0;
	while (buf[++i])
	{
		if (ft_isdigit(buf[i]) && !g_tc.col && buf[i] != ';')
			g_tc.row = g_tc.row * 10 + buf[i] - '0';
		else if (ft_isdigit(buf[i]) || buf[i] == ';')
		{
			if (buf[i] == ';')
				i++;
			g_tc.col = g_tc.col * 10 + buf[i] - '0';
		}
	}
	g_tc.col--;
	g_tc.row--;
	g_tc.curr_col = g_tc.col;
	g_tc.curr_row = g_tc.row;
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	rewrite_line(char *str)
{
	clear_after(g_tc.row, g_tc.col);
	ft_putstr_fd(str, 1);
	move_cursor(g_tc.curr_row, g_tc.curr_col);
}
