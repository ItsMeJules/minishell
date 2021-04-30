/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:35:16 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/30 17:32:43 by tvachera         ###   ########.fr       */
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

void	add_node(t_btree **root, t_list *node)
{
	if (!(*root))
	{
		*root = btree_create_node(node);
		return ;
	}
	if (!(*root)->left && !is_leaf(*root))
		(*root)->left = btree_create_node(node);

	else if (!(*root)->right && !is_leaf(*root))
		(*root)->right = btree_create_node(node);
}

void	move_pipes_to_ast(t_btree **root, t_list *lexer)
{
	t_list	*new;

	while ((new = next_pipe(lexer)))
	{
		add_node(root, new);
		while ((new = next_redir(lexer)))
		{
			add_node(root, new);
			add_node(root, next_file(new->item));
		}
		add_node(root, next_command(lexer));
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
			add_node(&root, new);
		move_pipes_to_ast(&root, lexer);
		while ((new = next_redir(lexer)))
		{
			add_node(&root, new);
			add_node(&root, next_file(new->item));
		}
		if ((new = next_command(lexer)))
			add_node(&root, next_command);
		else
			return (root);
	}
}
