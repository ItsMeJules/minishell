/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:51:33 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/10 17:57:34 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env)
{
	t_env	*elem;

	while (env)
	{
		elem = (t_env *)env->content;
		printf("%s=%s\n", elem->var, elem->val);
		env = env->next	;
	}
	return (0);
}
