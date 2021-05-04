/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:35:16 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/04 12:23:03 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_leaf(t_btree *root)
{
	t_list	*elem;

	elem = (t_list *)root->item;
	if (is_strenum(((t_token *)elem->content)->token))
		return (true);
	return (false);
}

t_node	*create_node(t_list *elem, t_etype type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (0);
	node->elem = elem;
	node->type = type;
	return (node);
}

bool	is_leaf(t_btree *leaf)
{
	if (((t_nbode *)leaf->item)->type == CMD
		|| ((t_nbode *)leaf->item)->type == FL)
		return (true);
	return (false);
}

bool	add_node(t_btree **root, t_list *elem, t_etype type)
{
	if (!(*root))
	{
		*root = btree_create_node(create_node(node, type));
		return (true);
	}
	else if (is_leaf(*root))
		return (false);
	else if (add_node(&(*root)->left, elem, type))
		return (true);
	return (add_node(&(*root)->right, elem, type));
}

void	move_pipes_to_ast(t_btree **root, t_list *lexer)
{
	t_list	*new;

	while ((new = next_pipe(lexer)))
	{
		add_node(root, new, PIPE);
		while ((new = next_redir(lexer)))
		{
			add_node(root, new, RDR);
			add_node(root, next_file(new->item), FL);
		}
		add_node(root, next_command(lexer), CMD);
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
			add_node(&root, new, SP);
		move_pipes_to_ast(&root, lexer);
		while ((new = next_redir(lexer)))
		{
			add_node(&root, new, RDR);
			add_node(&root, next_file(new->item), FL);
		}
		if ((new = next_command(lexer)))
			add_node(&root, next_command, CMD);
		else
			break ;
	}
	fix_ast_chains(root);
	return (root);
}
