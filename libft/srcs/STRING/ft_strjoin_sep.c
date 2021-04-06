/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:31:42 by jpeyron           #+#    #+#             */
/*   Updated: 2021/01/28 17:07:37 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	total_len(char const *s1, char const *s2, char const *sep)
{
	return ((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(sep) + 1));
}

static void		join_str(size_t *j, char *join, const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		join[*j] = s[i];
		(*j)++;
	}
}

char			*ft_strjoin_sep(char const *s1, char *sep, char const *s2)
{
	size_t	j;
	char	*join;

	j = 0;
	if (!s1 || !s2 || !sep)
		return (0);
	if (!(join = malloc(sizeof(char) * total_len(s1, s2, sep))))
		return (0);
	join_str(&j, join, s1);
	join_str(&j, join, sep);
	join_str(&j, join, s2);
	join[j] = 0;
	return (join);
}
