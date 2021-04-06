/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:20:17 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/16 16:37:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	c_bis;

	i = 0;
	c_bis = (char)c;
	while (s[i])
	{
		if (s[i] == c_bis)
			return ((char *)s + i);
		i++;
	}
	return (c == 0 ? (char *)s + i : 0);
}
