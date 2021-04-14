/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:19:32 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/14 17:16:11 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cursor_move(int mode, char *input)
{
	if (mode == LEFT_ARROW_KEY && g_tc.curr_col > g_tc.col)
		move_cursor(g_tc.curr_row, --g_tc.curr_col);
	else if (mode == RIGHT_ARROW_KEY
			&& g_tc.curr_col < g_tc.col + (int)ft_strlen(input))
		move_cursor(g_tc.curr_row, ++g_tc.curr_col);
}

char	*new_str(int str_size)
{
	char	*new_str;

	if (str_size == -1)
		return (NULL);
	if (!(new_str = malloc((str_size + 1) * sizeof(char))))	
	{
		//msg d'erreur ?
		return (NULL);
	}
	return (new_str);
}

void	handle_backspace(char **input)
{
	int		rel_col;
	int		i;
	int		j;
	char	*str;

	if (input == NULL)
		return ;
	str = new_str(ft_strlen(*input) - 1);
	if (!str)
		return ;
	rel_col = g_tc.curr_col - g_tc.col;
	i = -1;
	j = 0;
	while ((*input)[++i])
	{
		if (i != rel_col)
			str[i] = (*input)[j];
		j++;
	}
	str[i - 1] = 0;
	free(*input);
	*input = str;
	g_tc.curr_col--;
	rewrite_line(str);
}
