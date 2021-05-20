/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:43:01 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/20 15:54:08 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(char *path)
{
	int	fd;
	int	dir;

	fd = open(path, O_DIRECTORY);
	dir = 0;
	if (fd > 0)
		dir = 1;
	close(fd);
	return (dir);
}

int	is_exec_file(char *path)
{
	struct stat	f_stat;
	int			exec;
	int			success;

	success = stat(path, &f_stat);
	if (success == -1)
		return (1);
	exec = 0;
	if ((f_stat.st_mode & S_IRUSR) && (f_stat.st_mode & S_IXGRP
			|| f_stat.st_mode & S_IXUSR || f_stat.st_mode & S_IXOTH))
		exec = 1;
	return (!success && exec);
}

int	can_exec(char *file, t_list **env)
{
	if (is_dir(file))
	{
		ft_putstr_fd(TERM_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": is a directory\n", 2);
		mod_env(env, "?", "126");
		return (1);
	}
	else if (!is_exec_file(file))
	{
		ft_putstr_fd(TERM_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		mod_env(env, "?", "126");
		return (1);
	}
	return (0);
}

void	exec_cmd(t_exec *ex, t_list *cmd, t_setup *setup
		, void (*f)(t_exec *, t_setup *))
{
	if (!cmd)
		return (reset_ex(ex));
	if (!ft_strcmp(((t_token *)cmd->content)->str, "."))
		return (dot_only_err(setup, ex));
	if (link_fds(ex))
		return (link_error(ex, &setup->vars));
	ex->av = get_argv(cmd);
	ex->envp = get_envp(g_tc.env);
	if (!ex->av)
		return ((void)relink_fds(ex));
	if (is_builtin(ex->av[0]))
	{
		exec_builtin(ex->av, setup);
		return ((void)relink_fds(ex));
	}
	if (can_exec(ex->av[0], &setup->vars))
		return ((void)relink_fds(ex));
	ex->path = get_path(ex->av[0], g_tc.env, setup->vars);
	if (!ex->path)
		return ((void)relink_fds(ex));
	f(ex, setup);
	return ((void)relink_fds(ex));
}

void	exec(t_btree *ast, t_setup *setup, void (*f)(t_exec *, t_setup *))
{
	static t_exec	ex = {0, 1, -1, -1, false, NULL, NULL, NULL};

	if (!ast)
		return (reset_ex(&ex));
	if (((t_node *)ast->item)->type == SEMI)
	{
		exec(ast->left, setup, f);
		exec(ast->right, setup, f);
	}
	else if (((t_node *)ast->item)->type == PIPE)
		pipe_it(ast, setup, NULL);
	else
	{
		if (!ex.expand)
			expand_leafs(&ex, ast, &g_tc.env, &setup->vars);
		if (((t_node *)ast->item)->type == RDR
			&& set_redir(&ex, ast->item, ast->left->item))
			exec(ast->right, setup, f);
		else if (((t_node *)ast->item)->type == CMD)
			exec_cmd(&ex, ((t_node *)ast->item)->elem, setup, f);
	}
}
