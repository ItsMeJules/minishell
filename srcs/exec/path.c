/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:03:02 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 15:34:49 by tvachera         ###   ########.fr       */
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
	if (i && path[i - 1] != '/')
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

	if (ft_strlen(bin) == 0 || ft_strchr(bin, '/'))
		return (0);
	i = 0;
	errno = 0;
	while (paths[i])
	{
		path = join_path(paths[i], bin);
		ret = stat(path, &buf);
		if (ret == -1 && errno != ENOENT)
		{
			free(path);
			return (0);
		}
		else if (!ret)
			return (path);
		free(path);
		i++;
	}
	return (0);
}

char	*get_herebin(char *bin, t_list *vars)
{
	struct stat	buf;

	if (!ft_strchr(bin, '/'))
	{
		errno = ENOENT;
		return (NULL);
	}
	errno = 0;
	if (!stat(bin, &buf))
		return (ft_strdup(bin));
	else if (errno && errno != ENOENT)
	{
		mod_env(&vars, "?", "126");
		disp_fd_error(bin, strerror(errno));
		return (0);
	}
	return (0);
}

char	*get_path(char *bin, t_list *env, t_list *vars)
{
	char		**paths;
	char		*path;

	path = get_herebin(bin, vars);
	if (path)
		return (path);
	else if (errno != ENOENT)
		return (0);
	paths = init_paths(bin, env, vars);
	if (!paths)
		return (0);
	path = find_path(paths, bin);
	if (!path)
	{
		mod_env(&vars, "?", "127");
		disp_fd_error(bin, "command not found");
	}
	ft_free_split(paths);
	return (path);
}
