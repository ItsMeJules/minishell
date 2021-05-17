/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:30:51 by jules             #+#    #+#             */
/*   Updated: 2021/05/11 16:36:45 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_iter	*readu_input(t_history *history)
{
	t_iter	*iter;

	if (!(iter = malloc(sizeof(t_iter))))
		return (NULL);
	iter->i = 0;
	iter->err = NULL;
	iter->line = NULL;
	read_bpb(&iter->line, history);
	history->pos = -1;
	ft_putstr_fd(NORMAL, 1);
	return (iter);
}

void	print_prompt(char *path)
{
	char	*curr_dir;

	ft_putstr_fd(CYAN, 1);
	ft_putstr_fd("minishit ", 1);
	ft_putstr_fd(BOLD, 1);
	ft_putstr_fd(WHITE, 1);
	ft_putstr_fd("$", 1);
	ft_putstr_fd(LIGHT_CYAN, 1);
	curr_dir = ft_strrchr(path, '/');
	if (curr_dir)
		ft_putstr_fd(curr_dir + 1, 1);
	else
		ft_putstr_fd(path, 1);
	ft_putstr_fd(DARK_GRAY, 1);
	ft_putstr_fd("> ", 1);
	ft_putstr_fd(DEFAULT_COLOR, 1);
}

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
