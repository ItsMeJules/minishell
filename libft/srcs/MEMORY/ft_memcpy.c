/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:20:01 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/17 10:30:18 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d_bis;
	unsigned char	*s_bis;

	i = 0;
	if (!dest && !src)
		return (0);
	d_bis = (unsigned char *)dest;
	s_bis = (unsigned char *)src;
	while (i < n)
	{
		d_bis[i] = s_bis[i];
		i++;
	}
	return (dest);
}
