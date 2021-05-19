/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:29:49 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 13:59:46 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (((t_node *)leaf->item)->type == CMD
		|| ((t_node *)leaf->item)->type == FL);
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
