/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:30:51 by jules             #+#    #+#             */
/*   Updated: 2021/04/08 15:06:10 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_termcap()
{
	int		ret_ent;
	char	*term;

	term = getenv("TERM");
	if (!term)
	{
		printf(TERM_ENV_NOT_FOUND);
		return (-1);
	}
	ret_ent = tgetent(NULL, term);
	if (ret_ent == -1)
	{
		printf(TERMCAP_DB_ACCESS);
		return (-1);
	}
	else if (ret_ent == 0)
	{
		printf(TERM_TYPE_NOT_DEFINED, term);
		return (-1);
	}
	return (0);
}
