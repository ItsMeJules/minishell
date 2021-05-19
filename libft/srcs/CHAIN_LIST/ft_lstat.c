/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:39:50 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/19 14:47:05 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstat(t_list *begin_list, unsigned int nbr)
{
	unsigned int	i;

	i = 0;
	if (!begin_list)
		return (0);
	while (begin_list && i < nbr)
	{
		begin_list = begin_list->next;
		i++;
	}
	if (i == nbr)
		return (begin_list);
	return (0);
}
