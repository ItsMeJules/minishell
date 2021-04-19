/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:34:32 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/19 13:44:47 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*btree_search_item(t_btree *root, void *data_ref
		, int (*cmpf)(void *, void *))
{
	void	*data;

	if (!root || !data_ref)
		return (0);
	if (cmpf(data_ref, root->item) == 0)
		return (root->item);
	if (root->left)
	{
		if ((data = btree_search_item(root->left, data_ref, cmpf)))
			return (data);
	}
	if (root->right)
		return (btree_search_item(root->right, data_ref, cmpf));
	return (0);
}
