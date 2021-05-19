/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:46:08 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/19 14:50:19 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_paths(char **paths, char *bin, t_list *env, t_list *vars)
{
	if (is_var(env, "PATH"))
		paths = ft_split(get_env_val(env, "PATH"), ":");
	else if (is_var(vars, "PATH"))
		paths = ft_split(get_env_val(vars, "PATH"), ":");
	else
	{
		mod_env(&vars, "?", "127");
		disp_fd_error(bin, "command not found");
		return (0);
	}
	return (1);
}
