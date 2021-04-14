/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:35:18 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/14 16:10:58 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_term_mode(t_termcap *tc, int on)
{
	struct termios	raw;

	tcgetattr(0, &tc->o_termios);
	if (on)
	{
		raw = tc->o_termios;
		raw.c_lflag &= ~(ECHO | ICANON);

		tcsetattr(0, TCSAFLUSH, &raw);
	}
	else
		tcsetattr(0, TCSAFLUSH, &tc->o_termios);
}

int	init_termcap(t_termcap *tc)
{
	int		ret_ent;
	char	*term;

	if (!(term = getenv("TERM")))
	{
		printf(TERM_ENV_NOT_FOUND);
		return (-1);
	}
	if ((ret_ent = tgetent(NULL, term)) == -1)
	{
		printf(TERMCAP_DB_ACCESS);
		return (-1);
	}
	else if (ret_ent == 0)
	{
		printf(TERM_TYPE_NOT_DEFINED, term);
		return (-1);
	}
	change_term_mode(tc, 1);
	return (0);
}
