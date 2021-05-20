/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:46:49 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/20 17:31:40 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "exit"));
}

void	exec_builtin(char **cmd, t_setup *setup)
{
	int		ret;
	char	*nbr;

	ret = 0;
	if (!ft_strcmp(cmd[0], "echo"))
		ret = ft_echo(ft_split_size(cmd), cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		ret = ft_env(g_tc.env);
	else if (!ft_strcmp(cmd[0], "cd"))
		ret = ft_cd(ft_split_size(cmd), cmd, g_tc.env);
	else if (!ft_strcmp(cmd[0], "unset"))
		ret = unset(ft_split_size(cmd), cmd, &g_tc.env, &setup->vars);
	else if (!ft_strcmp(cmd[0], "export"))
		ret = export(ft_split_size(cmd), cmd, &g_tc.env, &setup->vars);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ret = ft_pwd(g_tc.env, setup->vars);
	else if (!ft_strcmp(cmd[0], "exit"))
		ret = ft_exit(ft_split_size(cmd), cmd, setup);
	nbr = ft_itoa(ret);
	mod_env(&setup->vars, "?", nbr);
	free(nbr);
}
