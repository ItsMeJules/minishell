/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:43:01 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/11 14:21:03 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_fds(t_exec *ex, int close, int *in, int *out)
{
	if (!close)
	{
		*in = dup(0);
		*out = dup(1);
		if (dup2(ex->fd_in, 0) < 0 || dup2(ex->fd_out, 1) < 0)
			return (1);
	}
	else
	{
		if (dup2(*in, 0) < 0  || dup2(*out, 1) < 0)
			return (1);
		reset_ex(ex);
	}
	return (0);
}

void	exec_cmd(t_exec *ex, t_list *cmd, t_list **env, t_list **vars)
{
	char	**av;
	char	*path;
	int		out;
	int		in;

	if (handle_fds(ex, 0, &out, &in) || !cmd)
		return ((void)handle_fds(ex, 1, &in, &out));
	av = get_argv(cmd);
	if (!av)
		return ((void)handle_fds(ex, 1, &in, &out));
	if (is_builtin(av[0]))
	{
		exec_builtin(av, env, vars);
		return ((void)handle_fds(ex, 1, &in, &out));
	}
	path = get_path(av[0], *env, *vars);
	if (!path)
	{
		ft_free_split(av);
		return ((void)handle_fds(ex, 1, &in, &out));
	}
	mod_env(vars, "?", ft_itoa(exec_fork(av, path, vars)));
	free(path);
	ft_free_split(av);
	handle_fds(ex, 1, &in, &out);
	return ((void)handle_fds(ex, 1, &in, &out));
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
	static t_exec	ex = {0, 1, false, NULL};

	if (!ast)
		return ;
	if (!ex.root)
		ex.root = ast;
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
