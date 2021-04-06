/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:08:47 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 15:02:27 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lst_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*current;
	t_list	*ptr;
	void	*content;

	ptr = *begin_list;
	while (ptr)
	{
		current = *begin_list;
		while (current->next)
		{
			if ((*cmp)(current->content, current->next->content) > 0)
			{
				content = current->content;
				current->content = current->next->content;
				current->next->content = content;
			}
			current = current->next;
		}
		ptr = ptr->next;
	}
}
