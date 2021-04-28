/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:00:32 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/27 16:02:27 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	btree_clear(t_btree *root)
{
	if (root->left)	
		btree_clear(root->left);
	if (root->right)
		btree_clear(root->right);
	free(root);
}
