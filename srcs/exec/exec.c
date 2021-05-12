/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:43:01 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/12 16:33:06 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_exec *ex, t_list *cmd, t_setup *setup
		, void (*f)(t_exec *, t_setup *))
{
	if (!cmd)
		return (reset_ex(ex));
	if (link_fds(ex))
		return (link_error(ex, &setup->vars));
	ex->av = get_argv(cmd);
	if (!ex->av)
		return ((void)relink_fds(ex));
	if (is_builtin(ex->av[0]))
	{
		exec_builtin(ex->av, setup);
		return ((void)relink_fds(ex));
	}
	ex->path = get_path(ex->av[0], setup->env, setup->vars);
	if (!ex->path)
		return ((void)relink_fds(ex));
	f(ex, setup);
	return ((void)relink_fds(ex));
}

void	exec(t_btree *ast, t_setup *setup)
{
	static t_exec	ex = {0, 1, -1, -1, false, NULL, NULL, NULL};

	if (!ast)
		return ;
	if (((t_node *)ast->item)->type == SEMI)
	{
		exec(ast->left, setup);
		exec(ast->right, setup);
	}
	else if (((t_node *)ast->item)->type == PIPE)
		pipe_it(ast, setup);
	else
	{
		if (!ex.expand)
			expand_leafs(&ex, ast, &setup->env, &setup->vars);
		if (((t_node *)ast->item)->type == RDR
			&& set_redir(&ex, ast->item, ast->left->item))
			exec(ast->right, setup);
		else if (((t_node *)ast->item)->type == CMD)
			exec_cmd(&ex, ((t_node *)ast->item)->elem, setup, &exec_fork);
	}
}
