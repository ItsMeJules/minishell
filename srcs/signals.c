/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 10:36:13 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/07 17:13:28 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_err(int signum)
{
	mod_env(&g_tc.env, "?", ft_itoa(128 + signum));
	g_tc.signal = signum;
}

void	handle_signal(int signum)
{
	update_env_err(signum);
	if (signum == SIGINT)
	{
		ft_putstr_fd("^C\n", 1);
		print_prompt(get_env_val(g_tc.env, "PWD"));
		get_cursor_pos();
		g_tc.cursor_pos = 0;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit (core dumped)", 1);
	}
}
