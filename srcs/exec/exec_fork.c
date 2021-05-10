/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:45:09 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/10 18:06:15 by jpeyron          ###   ########.fr       */
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
