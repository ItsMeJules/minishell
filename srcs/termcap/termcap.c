/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:30:51 by jules             #+#    #+#             */
/*   Updated: 2021/04/08 17:25:14 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_termcap(t_termcap *tc)
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
	change_term_mode(tc, 1);
	return (0);
}

int		addto_input(char buf[4], char **input)
{
	char	*tmp;

	buf[1] = 0;
	write(1, buf, 1);
	if (buf[0] == '\n')
		return (1);
	if (*input)
	{
		tmp = *input;
		*input = ft_strjoin(*input, buf);
		free(tmp);
	}
	else
		*input = ft_strjoin("", buf);
	return (0);
}

void	handle_termcap(char buf[3])
{
	(void)buf;
}

int		read_bpb(char **input)
{
	char	buf[4];
	int		ret;

	while ((ret = read(0, buf, 3))) 
	{
		if (ret == 1 && addto_input(buf, input))
			return (1);
		else if (ret == 3)
		{
			buf[3] = 0;
			handle_termcap(buf);
		}
	}
	return (0);
}
