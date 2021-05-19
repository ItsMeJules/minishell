/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:46:08 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/19 15:35:00 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_paths(char *bin, t_list *env, t_list *vars)
{
	char	**paths;

	paths = NULL;
	if (is_var(env, "PATH"))
		paths = ft_split(get_env_val(env, "PATH"), ":");
	else if (is_var(vars, "PATH"))
		paths = ft_split(get_env_val(vars, "PATH"), ":");
	else
	{
		mod_env(&vars, "?", "127");
		disp_fd_error(bin, "command not found");
		return (NULL);
	}
	return (paths);
}
