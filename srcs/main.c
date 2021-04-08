/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/04/08 17:20:17 by jules            ###   ########.fr       */
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
	read_bpb(&input);
	iter->i = 0;
	iter->err = NULL;
	iter->line = input;
	return (iter);
}

void	disp_lexer(t_list *root);

int	main()
{
	t_iter		*iter;
	t_list		*list;
	t_termcap	tc;

	init_termcap(&tc);
	iter = readu_input();
	list = NULL;
	list = tokenize_input(iter);
	disp_lexer(list);
	lexer_free(list, iter);
	change_term_mode(&tc, 0);
	return (0);
}
