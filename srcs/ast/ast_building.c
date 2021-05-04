/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:29:49 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/04 12:34:19 by tvachera         ###   ########.fr       */
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

bool	add_node(t_btree **root, t_node *node)
{
	if (!(*root))
	{
		*root = btree_create_node(node);
		return (true);
	}
	else if (is_leaf(*root))
		return (false);
	else if (add_node(&(*root)->left, node))
		return (true);
	return (add_node(&(*root)->right, node));
}
