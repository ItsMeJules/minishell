/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:45:09 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/11 14:36:02 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_fork(char **av, char *path, t_list **env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = get_envp(*env);
	pid = fork();
	ft_putstr_fd("test", 1);
	for (int i = 0; envp[i]; i++)
		ft_putstr_fd(envp[i], 1);
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
