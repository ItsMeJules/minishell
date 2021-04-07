/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/04/07 14:42:05 by jules            ###   ########.fr       */
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
	t_iter	*iter;
	t_list	*list;
	t_token	*token;

	init_termcap();
	iter = readu_input();
	tokenize_input(iter, list);

	while (list->next)
	{
		token = (t_token *)list->data;
		printf("type: %s | str: %s\n", token->token, token->str);
		list = list->next;	
	}

	return (0);
}
