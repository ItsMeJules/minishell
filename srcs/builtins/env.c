/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:51:33 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/17 11:28:10 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env)
{
	t_env	*elem;

	while (env)
	{
		elem = (t_env *)env->content;
		write(1, elem->var, ft_strlen(elem->var));
		if (elem->val)
		{
			write(1, "=", 1);
			write(1, elem->val, ft_strlen(elem->val));
		}
		write(1, "\n", 1);
		env = env->next	;
	}
	return (0);
}
