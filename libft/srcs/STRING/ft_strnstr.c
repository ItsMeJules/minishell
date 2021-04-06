/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:20:33 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/16 16:23:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!(*s2) || !s2)
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		j = 0;
		while (s2[j] && s2[j] == s1[i] && s1[i] && i < n)
		{
			j++;
			i++;
		}
		if (!s2[j])
			return ((char *)&s1[i - j]);
		s1[i] ? i -= j - 1 : 0;
	}
	return (0);
}
