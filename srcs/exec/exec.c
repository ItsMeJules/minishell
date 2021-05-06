/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:43:01 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/06 18:22:09 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exex	init_ex(t_btree *root)
{
	t_exec	ex;

	ex.fd_in = 0;
	ex.fd_out = 1;
	ex.pipe = false;
	ex.root = root;
	return (ex);
}

void	reset_ex(t_exec *ex)
{
	if (ex->fd_in != 0)
	{
		close(ex->fd_in);
		ex->fd_in = 0;
	}
	if (ex->fd_out != 1)
	{
		close(ex->fd_out);
		ex->fd_out = 1;
	}
	ex->pipe = false;
}


// GERER EXPANSION
void	exec(t_btree *ast, t_list **env, t_list **vars)
{
	static t_exec	ex = NULL;

	if (!ast)
		return ;	
	if (!ex)
		ex = init_ex(ast);
	if (((t_node *)ast->item)->type == SEMI)
	{
		exec(ast->left, env, vars);
		reset_ex(&ex);
		exec(ast->right, env, vars);
	}
	else if (((t_node *)ast->item)->type == PIPE)
		exec_pipe(ast, env, vars);
	else if (((t_node *)ast->item)->type == RDR)
	{
		if (set_redir(&ex, ast, env, vars))
			exec(ast->right, env, vars);
	}
	else
		exec_cmd(&ex, ast, env, vars);
}
