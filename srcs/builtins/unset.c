/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:27:05 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/27 16:34:34 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_err(char *str)
{
	write(2, TERM_NAME, ft_strlen(TERM_NAME));
	write(2, ": unset: `", 10);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	unset(int argc, char **argv, t_list **env, t_list **vars)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (i < argc)
	{
		if (is_declaration(argv[i]))
			ret = unset_err(argv[i]);
		else if (is_var(*env, argv[i]))
			remove_var(env, argv[i]);
		else if (is_var(*vars, argv[i]))
			remove_var(vars, argv[i]);
		i++;
	}
	return (ret);
}
