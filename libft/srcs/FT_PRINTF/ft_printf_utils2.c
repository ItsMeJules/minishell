/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:58:11 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/29 18:46:22 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		get_nb_len(unsigned long long nb, unsigned long long *pow,
				unsigned short base_len)
{
	unsigned int	len;

	len = 1;
	*pow = 1;
	while (*pow <= nb / base_len)
	{
		*pow *= base_len;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(long long n, char *base)
{
	long long			i;
	unsigned long long	pow;
	unsigned long long	nb;
	char				*word;
	unsigned short		base_len;

	i = n < 0;
	nb = n < 0 ? -n : n;
	base_len = ft_strlen(base);
	if (!(word = malloc(sizeof(char)
		* (get_nb_len(nb, &pow, base_len) + i + 1))))
		return (0);
	n < 0 ? word[0] = '-' : 0;
	while (pow >= 1)
	{
		word[i] = base[nb / pow];
		nb -= pow * (nb / pow);
		pow /= base_len;
		i++;
	}
	word[i] = 0;
	return (word);
}

char	*ft_unsigned_itoa_base(unsigned long long n, char *base)
{
	long long			i;
	unsigned long long	pow;
	char				*word;
	unsigned short		base_len;

	i = 0;
	base_len = ft_strlen(base);
	if (!(word = malloc(sizeof(char)
		* (get_nb_len(n, &pow, base_len) + 1))))
		return (0);
	while (pow >= 1)
	{
		word[i] = base[n / pow];
		n -= pow * (n / pow);
		pow /= base_len;
		i++;
	}
	word[i] = 0;
	return (word);
}

short	is_valid(char c)
{
	size_t		i;
	static char	*valid = VALID;

	i = 0;
	while (valid[i])
	{
		if (valid[i] == c)
			return (TRUE);
		i++;
	}
	return (is_specifier(c));
}

short	is_specifier(char c)
{
	size_t		i;
	static char	*specifier = SPECIFIERS;

	i = 0;
	while (specifier[i])
	{
		if (specifier[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
