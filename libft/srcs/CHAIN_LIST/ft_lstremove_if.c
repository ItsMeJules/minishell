/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:11:45 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/14 16:13:54 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstremove_if(t_list **begin_list, void *data_ref, int (*cmp)()
		, void (*free_fct)(void *))
{
	t_list	*element;
	t_list	*temp;

	while (*begin_list && (*cmp)((*begin_list)->content, data_ref) == 0)
	{
		temp = *begin_list;
		*begin_list = (*begin_list)->next;
		(*free_fct)(temp->content);
		free(temp);
	}
	element = *begin_list;
	while (element && element->next)
	{
		if ((*cmp)(element->next->content, data_ref) == 0)
		{
			temp = element->next;
			element->next = element->next->next;
			(*free_fct)(temp->content);
			free(temp);
		}
		else
			element = element->next;
	}
}
