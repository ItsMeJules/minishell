/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:45:09 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/11 15:41:21 by tvachera         ###   ########.fr       */
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

int	exec_fork(char **av, char *path, t_list **env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = get_envp(*env);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, av, envp) == -1)
			exit(1);
	}
	else if (pid != -1)
	{
		if (waitpid(pid, &status, 0) == -1)
			exit(1);
		return (WEXITSTATUS(status));
	}
	return (1);
}
