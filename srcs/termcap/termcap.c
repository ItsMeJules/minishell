/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:30:51 by jules             #+#    #+#             */
/*   Updated: 2021/04/21 16:34:08 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_termcap(char buf[4], char **input, t_history *history)
{
	if (is_tckey(buf, LEFT_ARROW_KEY))
		handle_cursor_move_left();
	else if (is_tckey(buf, RIGHT_ARROW_KEY))
		handle_cursor_move_right(input);
	if (is_tckey(buf, DOWN_ARROW_KEY))
		handle_down_arrow(history, input);
	else if (is_tckey(buf, UP_ARROW_KEY))
		handle_up_arrow(history, input);
	else if (is_tckey(buf, BACKSPACE_KEY))
		handle_backspace(input);
	else if (buf[0] == 4 && input && *input)
		handle_ctrld(input);
}

int		read_bpb(char **input, t_history *history)
{
	char	buf[4];
	int		ret;

	while ((ret = read(0, buf, 3))) 
	{
		buf[ret] = 0;
		if (ret == 1 && !is_tckey(buf, BACKSPACE_KEY)
				&& buf[0] != 4 && add_input(buf[0], input))
			return (1);
		else if (ret == 3 || is_tckey(buf, BACKSPACE_KEY) || buf[0] == 4)
			handle_termcap(buf, input, history);
	}
	return (0);
}
