/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_elems.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:48:59 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/27 16:28:58 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*next_sep(t_list *lexer)
{
	t_list	*node;
	t_token	*token;

	node = NULL;
	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (token->token == SEMI)
		{
			ft_lstadd_back(&node, ft_lstnew(new_node(false, NULL, NULL)));
			return (node);
		}
		lexer = lexer->next;
	}
	return (NULL);
}
