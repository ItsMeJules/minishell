/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:28:44 by jules             #+#    #+#             */
/*   Updated: 2021/04/12 13:48:24 by jules            ###   ########.fr       */
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
