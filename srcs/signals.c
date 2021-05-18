/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 10:36:13 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/18 12:47:29 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		if (g_tc.forked)
			ft_putchar_fd('\n', 1);
		else
		{
			g_tc.signal = 1;
			ft_putchar_fd('\n', 1);
			print_prompt(get_env_val(g_tc.env, "PWD"));
		}
	}
	else if (signum == SIGQUIT && g_tc.forked)
	{
		ft_putstr_fd("Quit: 3", 1);
		ft_putchar_fd('\n', 1);
	}
}
