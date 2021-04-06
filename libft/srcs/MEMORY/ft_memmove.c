/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:20:03 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/16 16:36:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d_bis;
	unsigned char	*s_bis;

	d_bis = (unsigned char *)dst;
	s_bis = (unsigned char *)src;
	if (d_bis == s_bis)
		return (dst);
	if (d_bis > s_bis)
	{
		s_bis += len - 1;
		d_bis += len - 1;
		while (len--)
			*d_bis-- = *s_bis--;
	}
	else
	{
		while (len--)
			*d_bis++ = *s_bis++;
	}
	return (dst);
}
