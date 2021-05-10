/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:03:02 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/10 15:00:21 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var(t_list *list, char *name)
{
	t_env	*elem;

	while (list)
	{
		elem = (t_env *)list->content;
		if (!ft_strcmp(elem->var, name))
			return (true);
		list = list->next;
	}
	return (false);
}

char	*join_path(char *path, char *bin)
{
	size_t	i;
	char	*tmp;
	char	*ret;

	i = 0;
	while (path[i])
		i++;
	if (i && path[i - 1] != '/' )
	{
		tmp = ft_strjoin(path, "/");
		ret = ft_strjoin(tmp, bin);
		free(tmp);
	}
	else
		ret = ft_strjoin(path, bin);
	return (ret);
}

char	*find_path(char **paths, char *bin)
{
	size_t		i;
	struct stat	buf;
	char		*path;
	int			ret;

	i = 0;
	while (paths[i])
	{
		path = join_path(paths[i], bin);
		ret = stat(path, &buf);
		if (ret == -1 && errno != ENOENT)
			return (0);
		else if (!ret)
			return (path);
		i++;
	}
	return (0);
}

char	*get_path(char *bin, t_list *env, t_list *vars)
{
	char	**paths;
	char	*path;

	if (is_var(env, "PATH"))
		paths = ft_split(get_env_val(env, "PATH"), ":");
	else if (is_var(vars, "PATH"))
		paths = ft_split(get_env_val(vars, "PATH"), ":");
	else
		return (0);
	path = find_path(paths, bin);
	printf("%s\n", path);
	ft_free_split(paths);
	return (path);
}

int		is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") || ft_strcmp(cmd, "ls")
			|| ft_strcmp(cmd, "cd") || ft_strcmp(cmd, "export")
			|| ft_strcmp(cmd, "unset") || ft_strcmp(cmd, "pwd")
			|| ft_strcmp(cmd, "exit"));
}
