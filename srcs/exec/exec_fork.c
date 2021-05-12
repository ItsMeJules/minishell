/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:45:09 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/12 12:06:12 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	relink_fds(t_exec *ex)
{
	if (ex->fd_in == 0 && ex->fd_out == 1)
		return (reset_ex(ex));
	if (ex->fd_in != 0)
	{
		if (dup2(ex->in, 0) < 0)
			close(ex->in);
	}
	if (ex->fd_out != 1)
	{
		if (dup2(ex->out, 1) < 0)
			close(ex->out);
	}
	reset_ex(ex);
}

int		link_fds(t_exec *ex)
{
	if (ex->fd_in == 0 && ex->fd_out == 1)
		return (0);
	if (ex->fd_in != 0)
	{
		ex->in = dup(0);
		if (dup2(ex->fd_in, 0) < 0)
		{
			close(ex->in);
			reset_ex(ex);
			return (1);
		}
	}
	if (ex->fd_out != 1)
	{
		ex->out = dup(1);
		if (dup2(ex->fd_out, 1) < 0)
		{
			close(ex->out);
			reset_ex(ex);
			return (1);
		}
	}
	return (0);
}

void	link_error(t_exec *ex, t_list **vars)
{
	relink_fds(ex);
	if (errno)
		ft_putstr_fd(strerror(errno), 1);
	ft_putchar_fd('\n', 1);
	mod_env(vars, "?", "1");
}

void	quit_shell(char **envp, char *path, char **av, t_setup *setup)
{
	if (envp)
		ft_free_split(envp);
	if (path)
		free(path);
	if (av)
		free_on_exit(setup, av, 1);
	else
		free_on_exit(setup, av, 0);
	exit(1);
	return (1);
}

int		exec_fork(char **av, char *path, t_setup *setup)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = get_envp(setup->env);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, av, envp) == -1)
			quit_shell(envp, path, av, setup);
	}
	else if (pid != -1)
	{
		if (waitpid(pid, &status, 0) == -1)
			quit_shell(envp, path, av, setup);
		ft_free_split(envp);
		//verifier commment l'enfant a quiite
		return (WEXITSTATUS(status));
	}
	ft_free_split(envp);
	return (1);
}
