/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/04/07 16:07:52 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_iter	*readu_input()
{
	char	*input;
	t_iter	*iter;

	if (!(iter = malloc(sizeof(t_iter))))
	{
		return (NULL);
	}
	get_next_line(0, &input);
	iter->i = 0;
	iter->err = 0;
	iter->line = input;
	return (iter);
}

int	main()
{
	t_iter	*iter;
	t_list	*list;
	t_token	*token;

	iter = readu_input();
	list = NULL;
	init_termcap();
	list = tokenize_input(iter);

	ft_lstclear(&list, free_token);
	free(iter->line);
	free(iter);
	return (0);
}
