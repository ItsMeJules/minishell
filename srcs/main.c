/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/04/07 12:47:52 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_iter	*readu_input()
{
	char	*input;
	t_iter	iter;

	if (ft_strcmp(get_next_line(0, &input), "exit") != 0)
	{
		iter.i = 0;
		iter.err = 0;
		iter.line = input;
		return (&line);
	}
	return (NULL);
}

int	main()
{
	init_termcap();
	readu_input();
	return (0);
}
