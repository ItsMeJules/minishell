/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:20:02 by jules             #+#    #+#             */
/*   Updated: 2021/05/21 13:46:39 by jpeyron          ###   ########.fr       */
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

int	skip_n_opt(bool nl, int *i)
{
	if (nl && *i == 1)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	ft_echo(int ac, char **av)
{
	bool	nl;
	bool	p_opt;
	int		i;

	nl = false;
	i = 1;
	if (ac > 1)
		nl = is_n_opt(av[1]);
	while (i < ac)
	{
		if (skip_n_opt(nl, &i))
			continue ;
		if (!is_n_opt(av[i]))
			p_opt = true;
		if (p_opt)
		{
			ft_putstr_fd(av[i], 1);
			if (i + 1 != ac)
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
	if (!nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
