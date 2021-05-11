/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:43:01 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/11 17:09:27 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_exec *ex, t_list *cmd, t_setup *setup)
{
	char	**av;
	char	*path;

	if (!cmd)
		return (reset_ex(ex));
	if (link_fds(ex))
		return (link_error(ex, &setup->vars));
	av = get_argv(cmd);
	if (!av)
		return ((void)relink_fds(ex));
	if (is_builtin(av[0]))
	{
		exec_builtin(av, setup);
		return ((void)relink_fds(ex));
	}
	path = get_path(av[0], setup->env, setup->vars);
	if (!path)
	{
		ft_free_split(av);
		return ((void)relink_fds(ex));
	}
	mod_env(&setup->vars, "?", ft_itoa(exec_fork(av, path, &setup->env)));
	free(path);
	ft_free_split(av);
	return ((void)relink_fds(ex));
}

void	exec_pipe(t_btree *ast, t_setup *setup)
{
	(void)ast;
	(void)setup;
	// A ECRIRE
	return ;
}

void	exec(t_btree *ast, t_setup *setup)
{
	static t_exec	ex = {0, 1, -1, -1, false};

	if (!ast)
		return ;
	if (((t_node *)ast->item)->type == SEMI)
	{
		exec(ast->left, setup);
		exec(ast->right, setup);
	}
	else if (((t_node *)ast->item)->type == PIPE)
		exec_pipe(ast, setup);
	else
	{
		if (!ex.expand)
			expand_leafs(&ex, ast, &setup->env, &setup->vars);
		if (((t_node *)ast->item)->type == RDR
			&& set_redir(&ex, ast->item, ast->left->item))
			exec(ast->right, setup);
		else if (((t_node *)ast->item)->type == CMD)
			exec_cmd(&ex, ((t_node *)ast->item)->elem, setup);
	}
}
