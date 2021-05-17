/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:20:02 by jules             #+#    #+#             */
/*   Updated: 2021/05/17 11:37:28 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_n_opt(char *arg)
{
	int	i;
	
	if (arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (!arg[i]);
}

int		ft_echo(int ac, char **av)
{
	bool	nl;
	int		i;

	nl = false;
	i = 1;
	if (ac > 1)
		nl = is_n_opt(av[1]);
	while (i < ac)
	{
		if (nl && i == 1)
		{
			i++;
			continue ;
		}
		ft_putstr_fd(av[i], 1);
		if (i + 1 != ac)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
