/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:30:51 by jules             #+#    #+#             */
/*   Updated: 2021/04/14 15:18:55 by jpeyron          ###   ########.fr       */
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

int		add_input(char buf[4], char **input)
{
	char	*tmp;

	write(1, buf, 1);
	if (buf[0] == '\n')
		return (1);
	if (*input)
	{
		tmp = *input;
		*input = ft_strjoin(*input, buf);
		free(tmp);
	}
	else
		*input = ft_strjoin("", buf);
	return (0);
}

void	handle_termcap(char buf[4])
{
	if (is_tckey(buf, LEFT_ARROW_KEY))
		move_cursor(g_tc.curr_row, g_tc.curr_col--);
}

int		read_bpb(char **input)
{
	char	buf[4];
	int		ret;

	while ((ret = read(0, buf, 3))) 
	{
		buf[ret] = 0;
		if (ret == 1 && !is_tckey(buf, BACKSPACE_KEY) && add_input(buf, input))
			return (1);
		else if (ret == 3 || is_tckey(buf, BACKSPACE_KEY))
			handle_termcap(buf);
	}
	return (0);
}
