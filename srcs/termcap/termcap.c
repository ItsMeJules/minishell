/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:30:51 by jules             #+#    #+#             */
/*   Updated: 2021/04/14 17:16:00 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_char(char c, char *new_str, int str_size, char **input)
{
	int	rel_col;
	int	i;
	int	j;
	
	rel_col = g_tc.curr_col - g_tc.col;
	i = -1;	
	j = 0;
	while (++i < str_size)
	{
		if (i == rel_col)
			new_str[i] = c;
		else
			new_str[i] = (*input)[j++];
	}
	new_str[i] = 0;
	free(*input);
	*input = new_str;
}

int		add_input(char c, char **input)
{
	char	*new_str;
	int		str_size; 

	if (c == '\n')
		return (1);
	str_size = *input == NULL ? 1 : ft_strlen(*input) + 1;
	if (!(new_str = malloc((str_size + 1) * sizeof(char))))
	{
		//msg d'erreur ?
		return (0);
	}
	insert_char(c, new_str, str_size, input);
	g_tc.curr_col++;
	rewrite_line(new_str);
	return (0);
}

void	handle_termcap(char buf[4], char **input)
{
	if (is_tckey(buf, LEFT_ARROW_KEY))
		handle_cursor_move(LEFT_ARROW_KEY, *input);
	else if (is_tckey(buf, RIGHT_ARROW_KEY))
		handle_cursor_move(RIGHT_ARROW_KEY, *input);
	if (is_tckey(buf, DOWN_ARROW_KEY))
		handle_cursor_move(DOWN_ARROW_KEY, *input);
	else if (is_tckey(buf, UP_ARROW_KEY))
		handle_cursor_move(UP_ARROW_KEY, *input);
	else if (is_tckey(buf, BACKSPACE_KEY))
		handle_backspace(input);
}

int		read_bpb(char **input)
{
	char	buf[4];
	int		ret;

	while ((ret = read(0, buf, 3))) 
	{
		buf[ret] = 0;
		if (ret == 1 && !is_tckey(buf, BACKSPACE_KEY)
				&& add_input(buf[0], input))
			return (1);
		else if (ret == 3 || is_tckey(buf, BACKSPACE_KEY))
			handle_termcap(buf, input);
	}
	return (0);
}
