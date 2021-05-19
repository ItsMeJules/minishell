/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:18:25 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 15:06:40 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

t_btree				*btree_create_node(void *item);
void				btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void				btree_apply_infix(t_btree *root, void (*applyf)(void *));
void				btree_apply_suffix(t_btree *root, void (*applyf)(void *));
void				btree_insert_data(t_btree **root, void *item,
						int (*cmpf)(void *, void *));
void				*btree_search_item(t_btree *root, void *data_ref,
						int (*cmpf)(void *, void *));
int					btree_level_count(t_btree *root);
void				btree_apply_by_level(t_btree *root, void (*applyf)
						(void *item, int current_level, int is_first_elem));
void				btree_clear(t_btree *root, void (*del)(void *));

#endif
