/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:59:53 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/19 15:56:39 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_shell2(t_setup *setup)
{
	btree_clear(setup->ast, free_ast_item);
	ft_lstclear(&g_tc.env, &del_env_elem);
	ft_lstclear(&setup->vars, &del_env_elem);
	free_history(setup->history);
	exit(1);
}

void	init_exit_ret(t_list *vars, int status)
{
	char	*str;

	str = ft_itoa(status);
	mod_env(&vars, "?", str);
	free(str);
}
