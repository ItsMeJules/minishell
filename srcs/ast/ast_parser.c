/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:39:16 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/22 11:54:04 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*parse_ast(t_list *lexer)
{
	t_btree	*bt;
	t_node	*root;
	t_token	*token;

	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (token->token)
		lexer = lexer->next;
	}
}
