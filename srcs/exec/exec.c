/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:43:01 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/11 15:39:59 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_exec *ex, t_list *cmd, t_list **env, t_list **vars)
{
	char	**av;
	char	*path;

	if (!cmd)
		return ;
	if (link_fds(ex))
		return (link_error(ex, vars));
	av = get_argv(cmd);
	if (!av)
		return ((void)relink_fds(ex));
	if (is_builtin(av[0]))
	{
		exec_builtin(av, env, vars);
		return ((void)relink_fds(ex));
	}
	path = get_path(av[0], *env, *vars);
	if (!path)
	{
		ft_free_split(av);
		return ((void)relink_fds(ex));
	}
	mod_env(vars, "?", ft_itoa(exec_fork(av, path, env)));
	free(path);
	ft_free_split(av);
	return ((void)relink_fds(ex));
}

void	exec_pipe(t_btree *ast, t_list **env, t_list **vars)
{
	(void)ast;
	(void)env;
	(void)vars;
	// A ECRIRE
	return ;
}

void	exec(t_btree *ast, t_list **env, t_list **vars)
{
	static t_exec	ex = {0, 1, -1, -1, false};

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
			exec_cmd(&ex, ((t_node *)ast->item)->elem, env, vars);
	}
}
