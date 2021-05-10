/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:43:01 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/10 14:36:18 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_exec *ex, t_list *cmd, t_list **env, t_list **vars);
{
	// A ECRIRE
	return ;
}

void	exec_pipe(t_btree *ast, t_list **env, t_list **vars)
{
	// A ECRIRE
	return ;
}

void	exec(t_btree *ast, t_list **env, t_list **vars)
{
	static t_exec	ex = {0, 1, false, ast};

	if (!ast)
		return ;
	if (((t_node *)ast->item)->type == SEMI)
	{
		exec(ast->left, env, vars);
		reset_ex(&ex);
		exec(ast->right, env, vars);
	}
	else if (((t_node *)ast->item)->type == PIPE)
		exec_pipe(ast, env, vars);
	else
	{
		if (!ex.expand)
			expand_leafs(&ex, ast, env, vars);
		if (((t_node *)ast->item)->type == RDR
			&& set_redir(&ex, ast->item, ast->left->item))
			exec(ast->right, env, vars);
		else if (((t_node *)ast->item)->type == CMD)
			exec_cmd(&ex, ((t_node *)ast->item)->elem);
	}
}
