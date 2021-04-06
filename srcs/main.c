/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/04/06 15:39:19 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	init()
{
	int		ret_ent;
	char	*term;

	term = getenv("TERM");
	if (!term)
	{
		print_error(TERM_ENV_NOT_FOUND, NULL);
		return (-1);
	}
	ret_ent = tgetent(NULL, term);
	if (ret_ent == -1)
	{
		print_error(TERMCAP_DB_ACCESS, NULL);
		return (-1);
	}
	else if (ret_ent == 0)
	{
		print_error(TERM_TYPE_NOT_DEFINED, term);
		return (-1);
	}
	return (0);
}
