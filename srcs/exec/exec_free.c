/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:59:53 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/12 16:56:25 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_shell2(t_setup *setup)
{
	btree_clear(setup->ast, free_ast_item);
	ft_lstclear(&setup->env, &del_env_elem);
	ft_lstclear(&setup->vars, &del_env_elem);
	free_history(setup->history);	
	exit(1);
}
