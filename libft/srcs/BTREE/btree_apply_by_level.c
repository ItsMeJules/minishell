/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_by_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:38:30 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:43:50 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	start(t_btree *root, unsigned int current_level
				, unsigned int *levels_list, void (*applyf)(void *item
				, int current_level, int is_first_elem))
{
	if (current_level == 1 && root)
	{
		applyf(root->item, levels_list[0], levels_list[1]);
		levels_list[1] = 0;
	}
	else if (current_level > 1 && root)
	{
		start(root->left, current_level - 1, levels_list, applyf);
		start(root->right, current_level - 1, levels_list, applyf);
	}
}

void	btree_apply_by_level(t_btree *root, void (*applyf)
				(void *item, int current_level, int is_first_elem))
{
	unsigned int	count;
	unsigned int	levels_list[2];
	unsigned int	i;

	i = 0;
	if (!root)
		return ;
	count = btree_level_count(root);
	while (i < count)
	{
		levels_list[0] = i;
		levels_list[1] = 1;
		start(root, ++i, levels_list, applyf);
	}
}
