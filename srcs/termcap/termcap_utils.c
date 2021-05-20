/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:26:46 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/20 15:46:03 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_tckey(char tc[4], int const_tc)
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
	else if (const_tc == HOME_KEY)
		return (tc[0] == 27 && tc[1] == 91 && tc[2] == 72);
	else if (const_tc == END_KEY)
		return (tc[0] == 27 && tc[1] == 91 && tc[2] == 70);
	else if (const_tc == CTRL_UP_KEYCOMB)
		return (tc[0] == 27 && tc[1] == 91 && tc[2] == 49 && tc[3] == 59
			&& tc[4] == 53 && tc[5] == 65);
	else if (const_tc == CTRL_DOWN_KEYCOMB)
		return (tc[0] == 27 && tc[1] == 91 && tc[2] == 49 && tc[3] == 59
			&& tc[4] == 53 && tc[5] == 66);
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

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	handle_ctrld_exit(t_setup *setup)
{
	int	status;

	status = ft_atoi(get_env_val(setup->vars, "?"));
	write(1, "exit\n", 5);
	ft_lstclear(&g_tc.env, &del_env_elem);
	ft_lstclear(&setup->vars, &del_env_elem);
	free_history(setup->history);
	change_term_mode(0);
	exit(status);
}

void	rewrite_line(char *str, int col)
{
	int	trow;

	trow = g_tc.curr_row;
	clear_after(g_tc.row, g_tc.col);
	move_cursor(g_tc.row, g_tc.col);
	ft_putstr_fd(str, 1);
	if (col == g_tc.w.ws_col)
	{
		if (trow + 1 == g_tc.w.ws_row && g_tc.row > 0)
		{
			write(1, " ", 1);
			move_cursor(trow, 0);
			g_tc.row--;
			return ;
		}
		move_cursor(trow + 1, 0);
	}
	else if (col < 0)
		move_cursor(trow - 1, g_tc.w.ws_row);
	else
		move_cursor(trow, col);
}
