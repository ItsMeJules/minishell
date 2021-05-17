/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:30:51 by jules             #+#    #+#             */
/*   Updated: 2021/05/17 17:37:26 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_iter	*readu_input(t_setup *setup)
{
	t_iter	*iter;

	if (!(iter = malloc(sizeof(t_iter))))
		return (NULL);
	iter->i = 0;
	iter->err = NULL;
	iter->line = NULL;
	read_bpb(&iter->line, setup);
	setup->history->pos = -1;
	ft_putstr_fd(NORMAL, 1);
	return (iter);
}

void	print_prompt(char *path)
{
	char	*curr_dir;

	ft_putstr_fd("\e[22m", 1);
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

void	handle_termcap(char buf[4], char **input, t_setup *setup)
{
	int	status;

	if (is_tckey(buf, LEFT_ARROW_KEY))
		handle_cursor_move_left();
	else if (is_tckey(buf, RIGHT_ARROW_KEY))
		handle_cursor_move_right(input);
	if (is_tckey(buf, DOWN_ARROW_KEY))
		handle_down_arrow(setup->history, input);
	else if (is_tckey(buf, UP_ARROW_KEY))
		handle_up_arrow(setup->history, input);
	else if (is_tckey(buf, BACKSPACE_KEY))
		handle_backspace(input);
	else if (buf[0] == 4 && input)
	{
		if (!*input || ft_strlen(*input) == 0)
		{
			status = ft_atoi(get_env_val(setup->vars, "?"));
			write(1, "exit\n", 5);
			ft_lstclear(&g_tc.env, &del_env_elem);
			ft_lstclear(&setup->vars, &del_env_elem);
			free_history(setup->history);
			exit(status);
		}
		else
			handle_ctrld(input);
	}
}

void	check_signal(char **input, t_list **vars)
{
	if (g_tc.signal != 0)
	{
		free(*input);
		*input = NULL;
		get_cursor_pos();
		g_tc.cursor_pos = 0;
		mod_env(vars, "?", "1");
		g_tc.signal = 0;
	}
}

int		read_bpb(char **input, t_setup *setup)
{
	char	buf[4];
	int		ret;

	while ((ret = read(0, buf, 3))) 
	{
		if (buf[0] == 9)
			continue ;
		check_signal(input, &setup->vars);
		buf[ret] = 0;
		if (ret == 1 && !is_tckey(buf, BACKSPACE_KEY)
				&& buf[0] != 4 && add_input(buf[0], input))
			return (1);
		else if (ret == 3 || is_tckey(buf, BACKSPACE_KEY) || buf[0] == 4)
			handle_termcap(buf, input, setup);
	}
	return (0);
}
