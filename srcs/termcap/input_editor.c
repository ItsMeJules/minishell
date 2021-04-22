/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:19:32 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/21 16:34:16 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	insert_char(char c, char *new_str, int str_size, char **input)
{
	int	i;
	int	j;
	
	i = -1;	
	j = 0;
	while (++i < str_size)
	{
		if (i == g_tc.cursor_pos)
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
	g_tc.cursor_pos++;
	rewrite_line(new_str, g_tc.curr_col + 1);
	return (0);
}

void	handle_ctrld(char **input)
{
	int		i;
	int		j;
	char	*new_str;
	
	if (g_tc.cursor_pos >= (int)ft_strlen(*input))
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
		if (i != g_tc.cursor_pos)
			new_str[j++] = (*input)[i];
	}
	new_str[j] = 0;
	free(*input);
	rewrite_line(*input = new_str, g_tc.curr_col);
}

void	handle_backspace(char **input)
{
	int		i;
	int		j;
	char	*str;

	if (input == NULL || *input == NULL || g_tc.curr_col <= g_tc.col)
		return ;
	str = new_str(ft_strlen(*input) - 1);
	if (!str)
		return ;
	i = 0;
	j = 0;
	g_tc.cursor_pos--;
	while ((*input)[j])
	{
		if (j == g_tc.cursor_pos)
			j++;
		else
			str[i++] = (*input)[j++];
	}
	str[i] = 0;
	free(*input);
	*input = str;
	rewrite_line(str, g_tc.curr_col - 1);
}