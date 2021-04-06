/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:19:57 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/16 16:22:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_bis;
	unsigned char	c_bis;

	i = 0;
	s_bis = (unsigned char *)s;
	c_bis = (unsigned char)c;
	while (i < n)
	{
		if (s_bis[i] == c_bis)
			return (s_bis + i);
		i++;
	}
	return (0);
}
