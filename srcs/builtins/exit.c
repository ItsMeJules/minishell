/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:42:33 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/19 12:32:12 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		string_is_num(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]) && (str[i] != '-' && str[i] != '+'))
		return (0);
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

void	free_on_exit(t_setup *setup, char **av, int free_av)
{
	btree_clear(setup->ast, free_ast_item);
	ft_lstclear(&g_tc.env, &del_env_elem);
	ft_lstclear(&setup->vars, &del_env_elem);
	free_history(setup->history);
	if (free_av)
		ft_free_split(av);
	if (g_tc.forked == 0)
		ft_putstr_fd("exit\n", 1);
}

int		ft_exit(int ac, char **av, t_setup *setup)
{
	int	ret;

	if (ac > 2)	
		return (print_error(1, NULL));
	else if (ac == 2)
	{
		free_on_exit(setup, av, !string_is_num(av[1]));
		if (!string_is_num(av[1]))
		{
			print_error(2, av[1]);
			exit(2);
		}
		else
		{
			ret = ft_atoi(av[1]);
			ft_free_split(av);
			exit(ret);
		}
	}
	else
	{
		ret = ft_atoi(get_env_val(setup->vars, "?"));
		free_on_exit(setup, av, 1);
		exit(ret);
		return (1);
	}
}
