/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:48:08 by jules             #+#    #+#             */
/*   Updated: 2021/05/11 15:46:32 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		dir_change_err(char *path)
{
	ft_putstr_fd(TERM_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int		cd_home(t_list *env)
{
	char	*home;
	char	path[4096];
	
	if (!is_var(env, "HOME"))
	{
		ft_putstr_fd(TERM_NAME, 2);
		ft_putstr_fd(": cd: HOME is not set !\n", 2);
		return (0);
	}
	home = get_env_val(env, "HOME");
	if (chdir(home))
		return (dir_change_err(home));
	mod_env(&env, "OLDPWD", get_env_val(env, "PWD"));
	mod_env(&env, "PWD", getcwd(path, 4096));
	return (1);
}

int		cd_oldpwd(t_list *env)
{
	char	*old_pwd;
	char	path[4096];
	
	if (!is_var(env, "OLDPWD"))
	{
		ft_putstr_fd(TERM_NAME, 2);
		ft_putstr_fd(": cd: OLDPWD is not set !\n", 2);
		return (0);
	}
	old_pwd = get_env_val(env, "OLDPWD");
	if (chdir(old_pwd))
		return (dir_change_err(old_pwd));
	mod_env(&env, "OLDPWD", get_env_val(env, "PWD"));
	mod_env(&env, "PWD", getcwd(path, 4096));
	return (1);
}

int		ft_cd(int ac, char **av, t_list *env)
{
	char	path[4096];

	if (ac > 2)
	{
		ft_putstr_fd(TERM_NAME, 2);
		ft_putstr_fd(": cd: too many arguments\n", 2);
		return (0);
	}
	if (!av[1])
		return (cd_home(env));	
	if (ft_strcmp("-", av[1]) == 0)
		return (cd_oldpwd(env));
	if (chdir(av[1]))
		return (dir_change_err(av[1]));
	mod_env(&env, "OLDPWD", get_env_val(env, "PWD"));
	mod_env(&env, "PWD", getcwd(path, 4096));
	return (1);
}
