/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:20:36 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/17 17:01:48 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static bool	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*trim;

	i = 0;
	start = 0;
	if (!s1)
		return (0);
	end = ft_strlen(s1);
	while (s1[start] && is_set(s1[start], set))
		start++;
	while (end >= 0 && is_set(s1[end - 1], set))
		end--;
	if (end < start)
		end = start;
	if (!(trim = malloc(sizeof(char) * (end - start + 1))))
		return (0);
	while (i < end - start)
	{
		trim[i] = s1[start + i];
		i++;
	}
	trim[i] = 0;
	return (trim);
}
