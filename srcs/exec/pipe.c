/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:42:46 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:50:40 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_nofork(t_exec *ex, t_setup *setup)
{
	if (execve(ex->path, ex->av, ex->envp) == -1)
		quit_shell(ex, setup);
}

int	how_exited(int status)
{
	if (WIFEXITED(status))
		return (0);
	else
		return (WTERMSIG(status));
}

void	dup_exec(int *prev_pfd, int *pfd, t_btree *dest, t_setup *setup)
{
	if (prev_pfd)
	{
		close(prev_pfd[1]);
		if (dup2(prev_pfd[0], 0) < 0)
			exit(1);
		close(prev_pfd[0]);
	}
	if (pfd)
	{
		close(pfd[0]);
		if (dup2(pfd[1], 1) < 0)
			exit(1);
		close(pfd[1]);
	}
	exec(dest, setup, &exec_nofork);
	exit(ft_atoi(get_env_val(setup->vars, "?")));
}

void	pipe_r(t_btree *ast, t_setup *setup, int *pfd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
		dup_exec(pfd, NULL, ast->right, setup);
	else if (pid < 0)
		quit_shell2(setup);
	g_tc.forked++;
	close(pfd[0]);
	if (waitpid(pid, &status, 0) < 0)
		quit_shell2(setup);
	g_tc.forked--;
	if (!how_exited(status))
		init_exit_ret(setup->vars, WEXITSTATUS(status));
	else
		init_exit_ret(setup->vars, how_exited(status) + 128);
}

void	pipe_it(t_btree *ast, t_setup *setup, int *prev_pfd)
{
	int		pfd[2];
	int		status;
	pid_t	pid;

	if (pipe(pfd) == -1)
		quit_shell2(setup);
	pid = fork();
	if (!pid)
		dup_exec(prev_pfd, pfd, ast->left, setup);
	else if (pid < 0)
		quit_shell2(setup);
	g_tc.forked++;
	close(pfd[1]);
	if (((t_node *)ast->right->item)->type == PIPE)
		pipe_it(ast->right, setup, pfd);
	else
		pipe_r(ast, setup, pfd);
	if (waitpid(pid, &status, 0) < 0)
		quit_shell2(setup);
	if (prev_pfd)
		close(prev_pfd[0]);
	g_tc.forked--;
}
