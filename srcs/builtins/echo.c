/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:20:02 by jules             #+#    #+#             */
/*   Updated: 2021/04/28 16:54:30 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(int ac, char **av)
{
	bool	nl;
	bool	printed;
	int		i;

	nl = false;
	printed = false;
	i = 1;
	while (i < ac)
	{
		while (!printed && av[i] && ft_strcmp(av[i], "-n") == 0)
		{
			nl = true;
			i++;
		}
		printed = true;
		ft_putstr_fd(av[i], 1);
		if (i + 1 != ac)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!nl)
		ft_putchar_fd('\n', 1);
	return (1);
}
