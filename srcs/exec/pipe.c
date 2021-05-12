/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:42:46 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/12 12:49:02 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_nofork(char **av, char *path, t_setup *setup)
{
	char	**envp;

	envp = get_envp(setup->env);
	if (execve(path, av, envp) == -1)
		quit_shell(envp, path, av, setup);
	ft_free_split(envp);
	return (1);
}

void	exec_pipe(t_btree *ast, t_setup *setup)
{
	static t_exec	ex = {0, 1, -1, -1, false};

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
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
}

void	pipe_lor(bool left, t_cmd *cmd, t_btree *ast, t_setup *setup)
{
	if (left)
	{
		close(cmd->pfd[0]);
		dup2(cmd->pfd[1], 1);
		exec_pipe(ast->left, setup);
		close(cmd->pfd[1]);
		return ;
	}
	if (waitpid(cmd->pid, &cmd->status, 0) == -1)
		quit_shell(NULL, NULL, NULL, setup);
	if (how_exited(cmd->status))
	{
		
	}
}

void	pipe_it(t_btree *ast, t_setup *setup)
{
	t_cmd	cmd;

	if (pipe(cmd.pfd) == -1)
		quit_shell(NULL, NULL, NULL, setup);
	cmd.pid = fork();
	if (cmd.pid == 0)
		pipe_lor(true, &cmd, ast, setup);
	else if (cmd.pid != -1)
	{ 
			
		// mettre ? a sa valeur	&& verifier comment l'enfant a quitte
	}
	return ;
}

