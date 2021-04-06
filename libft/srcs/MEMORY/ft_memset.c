/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:20:04 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/16 16:35:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*bis;

	i = 0;
	bis = (unsigned char *)b;
	while (i < n)
	{
		bis[i] = (unsigned char)c;
		i++;
	}
	return (bis);
}
