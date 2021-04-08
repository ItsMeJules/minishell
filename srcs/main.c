/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:08:03 by jules             #+#    #+#             */
/*   Updated: 2021/04/08 15:55:46 by tvachera         ###   ########.fr       */
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
	iter->err = NULL;
	iter->line = input;
	return (iter);
}

void	print_prompt()
{
	write(1, "minishit>", 9);
}

void	disp_lexer(t_list *root);

int	main()
{
	t_iter	*iter;
	t_list	*list;

	while (42)
	{
		print_prompt();
		iter = readu_input();
		list = NULL;
		init_termcap();
		list = tokenize_input(iter);
		disp_lexer(list);
		lexer_free(list, iter);
	}
	return (0);
}
