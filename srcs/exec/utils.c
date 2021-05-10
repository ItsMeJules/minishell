/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:01:32 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/10 15:42:12 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(char **cmd, t_list **env, t_list **vars)
{
	int	ret;

	if (ft_strcmp(cmd, "echo"))
		ret = ft_echo(ft_split_size(cmd), cmd);
	else if (ft_strcmp(cmd, "env"))
		ret = env(*env);
	else if (ft_strcmp(cmd, "cd"))
		ret = ft_cd(ft_split_size(cmd), cmd, *env);
	else if (ft_strcmp(cmd, "unset"))
		ret = unset(ft_split_size(cmd), cmd, env, vars);
	else if (ft_strcmp(cmd, "export"))
		ret = export(ft_split_size(cmd), cmd, env, vars);
	else if (ft_strcmp(cmd, "unset"))
		ret = unset(ft_split_size(cmd), cmd, env, vars);
	else if (ft_strcmp(cmd, "pwd"))
		ret = ft_pwd();
	else if (ft_strcmp(cmd, "exit"))
		ret = ft_exit(ft_split_size(cmd), cmd);
	mod_env(vars, "?", ft_itoa(ret));
}
