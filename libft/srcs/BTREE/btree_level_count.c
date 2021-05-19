/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:37:06 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:45:36 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	btree_level_count(t_btree *root)
{
	int	count;
	int	temp;

	count = 0;
	if (!root)
		return (0);
	if (root->left)
	{
		temp = btree_level_count(root->left);
		if (count < temp)
			count = temp;
	}
	if (root->right)
	{
		temp = btree_level_count(root->right);
		if (count < temp)
			count = temp;
	}
	return (count + 1);
}
