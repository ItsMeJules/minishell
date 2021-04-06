/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:20:35 by tvachera          #+#    #+#             */
/*   Updated: 2020/12/21 19:20:39 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	c_bis;

	i = (int)ft_strlen(s);
	c_bis = (char)c;
	if (c == 0)
		return ((char *)s + i);
	while (i--)
	{
		if (s[i] == c_bis)
			return ((char *)s + i);
	}
	return (0);
}
