/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:35:18 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/19 14:28:23 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_term_mode(int on)
{
	struct termios	raw;

	if (on)
	{
		tcgetattr(0, &g_tc.o_termios);
		raw = g_tc.o_termios;
		raw.c_lflag &= ~(ECHO | ICANON);
		tcsetattr(0, TCSAFLUSH, &raw);
	}
	else
		tcsetattr(0, TCSAFLUSH, &g_tc.o_termios);
}

int	init_termcap(void)
{
	int				ret_ent;
	char			*term;

	term = getenv("TERM");
	if (!term)
	{
		printf(TERM_ENV_NOT_FOUND);
		return (-1);
	}
	ret_ent = tgetent(NULL, term);
	if (ret_ent == -1)
	{
		printf(TERMCAP_DB_ACCESS);
		return (-1);
	}
	else if (ret_ent == 0)
	{
		printf(TERM_TYPE_NOT_DEFINED, term);
		return (-1);
	}
	change_term_mode(1);
	ioctl(1, TIOCGWINSZ, &g_tc.w);
	g_tc.cursor_pos = 0;
	return (0);
}
