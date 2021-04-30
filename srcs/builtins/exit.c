/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:42:33 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/30 13:55:52 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		string_is_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int		print_error(int type, char *str)
{
	if (type == 1)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd(TERM_NAME, 2);
		ft_putstr_fd(": too many arguments", 2);
	}
	else if (type == 2)
	{
		ft_putstr_fd(TERM_NAME, 2);
		ft_putstr_fd(": exit:", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is not a number !", 2);
	}
	return (0);
}

void	free_on_exit()
{
	ft_putstr_fd("exit\n", 1);
}

int		ft_exit(int ac, char **av)
{
	if (ac > 2)	
		return (print_error(1, NULL));
	else if (ac == 1)
	{
		free_on_exit();
		if (!string_is_num(av[1]))
		{
			print_error(2, av[1]);
			exit(2);
		}
		else
			exit(ft_atoi(av[1]));
	}
	else
	{
		//recuperer la valeur de retour de la derniere commande
		//exit avec la valeur de retour
		return (1);
	}
}
