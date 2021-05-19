/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:00:32 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:44:18 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	btree_clear(t_btree *root, void (*del)(void *))
{
	if (root->left)
		btree_clear(root->left, del);
	if (root->right)
		btree_clear(root->right, del);
	(*del)(root->item);
	free(root);
}
