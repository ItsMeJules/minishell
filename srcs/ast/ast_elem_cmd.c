/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_elem_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:20:54 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/30 17:45:17 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*skip_chev(t_list *lexer)
{
}

t_list	*break_chain(t_list *lexer)
{
	t_list	*tmp;

	if (!lexer)
		return (0);
	tmp = lexer->next;
	lexer->next = 0;
	return (tmp);
}

t_list	*next_command(t_list *lexer)
{
	static t_list	*elem = NULL;
	
	if (!elem)
		elem = lexer;
	else if (!is_chev(((t_token *)lexer->content)->token))
		elem = elem->next;
	else
		elem = break_chain(skip_chev(
	while (elem)	
}
