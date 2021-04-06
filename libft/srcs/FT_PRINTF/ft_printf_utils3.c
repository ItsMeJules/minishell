/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:27:24 by tvachera          #+#    #+#             */
/*   Updated: 2020/12/24 13:41:06 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*get_empty_line(void)
{
	char	*str;

	if (!(str = malloc(sizeof(char))))
		return (0);
	str[0] = 0;
	return (str);
}

char	*strndup2(const char *s1, size_t n, short active)
{
	unsigned int	i;
	char			*dest;

	i = 0;
	if (!s1)
		return (strndup2("(null)", active == TRUE ? n : 6, active));
	while (s1[i] && i < n)
		i++;
	if (!(dest = malloc(sizeof(char) * i + 1)))
		return (0);
	i = 0;
	while (s1[i] && i < n)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int		get_word(const char *str, size_t *index_str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '%')
		i++;
	write(1, str, i);
	*index_str += i;
	return (i);
}
