/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:42:46 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/12 17:29:01 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_nofork(t_exec *ex, t_setup *setup)
{
	if (execve(ex->path, ex->av, ex->envp) == -1)
		quit_shell(ex, setup);
}

void	exec_pipe(t_btree *ast, t_setup *setup)
{
	static t_exec	ex = {0, 1, -1, -1, false, NULL, NULL, NULL};

	if (!ast)
		return ;
	if (((t_node *)ast->item)->type == PIPE)
		pipe_it(ast, setup);
	else
	{
		if (!ex.expand)
			expand_leafs(&ex, ast, &setup->env, &setup->vars);
		if (((t_node *)ast->item)->type == RDR
			&& set_redir(&ex, ast->item, ast->left->item))
			exec(ast->right, setup);
		else if (((t_node *)ast->item)->type == CMD)
			exec_cmd(&ex, ((t_node *)ast->item)->elem, setup, &exec_nofork);
	}
}

int		how_exited(int status)
{
	if (WIFEXITED(status))
		return (0);
	else
		return (WTERMSIG(status));
}

void	pipe_l(t_cmd *cmd, t_btree *ast, t_setup *setup, bool reset)
{
	static t_cmd	*scmd = NULL;

	if (scmd == NULL)
	{
		scmd = cmd;
		close(cmd->pfd[0]);
		dup2(cmd->pfd[1], 1);
		exec_pipe(ast, setup);
	}
	else
	{
		close(cmd->pfd[1]);	
		dup2(cmd->pfd[0], 0);
		scmd = cmd;
		exec_pipe(ast, setup);
		close(cmd->pfd[0]);
		close(scmd->pfd[1]);
	}
	if (reset)
		scmd = NULL;
}

void	pipe_it(t_btree *ast, t_setup *setup)
{
	t_cmd	cmd;

	if (pipe(cmd.pfd) == -1)
		quit_shell2(setup);
	cmd.pid[0] = fork();
	if (cmd.pid[0] == 0)
		pipe_l(&cmd, ast->left, setup, 0);
	else if (cmd.pid[0] == -1)
		quit_shell2(setup);
	if (((t_node *)ast->right->item)->type == PIPE)
		pipe_it(ast->right, setup);
	else
	{
		cmd.pid[1] = fork();
		if (cmd.pid[1] == 0)
			pipe_l(&cmd, ast->right, setup, 1);
		else if (cmd.pid[1] == -1)
			quit_shell2(setup);
		printf("%d\n", cmd.pid[1]);
		if (waitpid(cmd.pid[1], &cmd.status[1], 0) == -1)
			quit_shell2(setup);
		if (!how_exited(cmd.status[1]))
			mod_env(&setup->vars, "?", ft_itoa(WEXITSTATUS(cmd.status[1])));
	}
	printf("first=%d\n", cmd.pid[1]);
	if (cmd.pid[0] == 0 && waitpid(cmd.pid[0], &cmd.status[0], 0) == -1)
		quit_shell2(setup);
}
