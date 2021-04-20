/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:30:51 by jules             #+#    #+#             */
/*   Updated: 2021/04/20 15:09:26 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_char(char c, char *new_str, int str_size, char **input)
{
	int	rel_col;
	int	i;
	int	j;
	
	rel_col = get_rel_col();
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
	{
		write(1, &c, 1);
		return (1);
	}
	str_size = *input == NULL ? 1 : ft_strlen(*input) + 1;
	if (!(new_str = malloc((str_size + 1) * sizeof(char))))
	{
		//msg d'erreur ?
		return (0);
	}
	insert_char(c, new_str, str_size, input);
	rewrite_line(new_str, g_tc.curr_col + 1);
	return (0);
}

void	handle_ctrld(char **input)
{
	int		rel_col;
	int		i;
	int		j;
	char	*new_str;
	
	rel_col = get_rel_col();
	if (rel_col >= (int)ft_strlen(*input))
		return ;
	i = -1;
	j = 0;
	if (!(new_str = malloc(ft_strlen(*input) * sizeof(char))))
	{
		//msg d'erreur ?
		return ;
	}
	while ((*input)[++i])
	{
		if (i != rel_col)
			new_str[j++] = (*input)[i];
	}
	new_str[j] = 0;
	free(*input);
	rewrite_line(*input = new_str, g_tc.curr_col);
}

void	handle_termcap(char buf[4], char **input, t_history *history)
{
	if (is_tckey(buf, LEFT_ARROW_KEY))
		handle_cursor_move(LEFT_ARROW_KEY, input, history);
	else if (is_tckey(buf, RIGHT_ARROW_KEY))
		handle_cursor_move(RIGHT_ARROW_KEY, input, history);
	if (is_tckey(buf, DOWN_ARROW_KEY))
		handle_cursor_move(DOWN_ARROW_KEY, input, history);
	else if (is_tckey(buf, UP_ARROW_KEY))
		handle_cursor_move(UP_ARROW_KEY, input, history);
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
