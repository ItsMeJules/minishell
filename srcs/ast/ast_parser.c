/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:35:16 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/04 12:37:19 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_pipes_to_ast(t_btree **root, t_list *lexer)
{
	t_list	*new;

	while ((new = next_pipe(lexer)))
	{
		add_node(root, create_node(new, PIPE));
		while ((new = next_redir(lexer)))
		{
			add_node(root, create_node(new, RDR));
			add_node(root, create_node(next_file(new->item), FL));
		}
		add_node(root, create_node(next_command(lexer), CMD));
	}
}

t_btree	*parse_ast(t_list *lexer)
{
	t_btree	*root;
	t_list	*new;

	root = NULL;
	while (42)
	{
		if ((new = next_sep(lexer)))
			add_node(&root, create_node(new, SP));
		move_pipes_to_ast(&root, lexer);
		while ((new = next_redir(lexer)))
		{
			add_node(&root, create_node(new, RDR));
			add_node(&root, create_node(next_file(new->item), FL));
		}
		if ((new = next_command(lexer)))
			add_node(&root, create_node(next_command, CMD));
		else
			break ;
	}
	fix_ast_chains(root);
	return (root);
}
