/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:19:56 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/16 16:32:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d_bis;
	unsigned char	*s_bis;

	i = 0;
	d_bis = (unsigned char *)dest;
	s_bis = (unsigned char *)src;
	while (i < n)
	{
		d_bis[i] = s_bis[i];
		if (s_bis[i] == (unsigned char)c)
			return (d_bis + i + 1);
		i++;
	}
	return (0);
}
