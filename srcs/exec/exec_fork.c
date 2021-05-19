/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:45:09 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/19 14:33:41 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	relink_fds(t_exec *ex)
{
	if (ex->fd_in == 0 && ex->fd_out == 1)
		return (reset_ex(ex));
	if (ex->fd_in != 0)
	{
		dup2(ex->in, 0);
		close(ex->in);
	}
	if (ex->fd_out != 1)
	{
		dup2(ex->out, 1);
		close(ex->out);
	}
	reset_ex(ex);
}

int	link_fds(t_exec *ex)
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

void	quit_shell(t_exec *ex, t_setup *setup)
{
	if (ex->envp)
		ft_free_split(ex->envp);
	if (ex->path)
		free(ex->path);
	if (ex->av)
		free_on_exit(setup, ex->av, 1);
	else
		free_on_exit(setup, ex->av, 0);
	exit(1);
}

void	exec_fork(t_exec *ex, t_setup *setup)
{
	pid_t	pid;
	int		status;
	char	*str;

	pid = fork();
	if (pid == 0 && execve(ex->path, ex->av, ex->envp) == -1)
		quit_shell(ex, setup);
	else if (pid < 0)
		quit_shell(ex, setup);
	g_tc.forked = 1;
	if (waitpid(pid, &status, 0) == -1)
		quit_shell(ex, setup);
	g_tc.forked = 0;
	if (!how_exited(status))
	{
		str = ft_itoa(WEXITSTATUS(status));
		mod_env(&setup->vars, "?", str);
		free(str);
	}
	else
	{
		str = ft_itoa(how_exited(status) + 128);
		mod_env(&setup->vars, "?", str);
		free(str);
	}
}
