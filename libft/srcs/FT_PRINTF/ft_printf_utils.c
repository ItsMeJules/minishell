/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:59:58 by tvachera          #+#    #+#             */
/*   Updated: 2020/12/24 13:52:43 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

long		ft_atoi_lg(const char *str)
{
	long	i;
	short	is_negative;
	long	nb;

	i = 0;
	is_negative = 1;
	nb = 0;
	while ((str[i] > 47 && str[i] < 58) && str[i])
	{
		nb *= 10;
		nb += str[i] - 48;
		i++;
	}
	return (nb * is_negative);
}

short		in_str(char c, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int			print_c(size_t width, char c)
{
	size_t	i;

	i = 0;
	while (i++ < width)
		write(1, &c, 1);
	return (width);
}
