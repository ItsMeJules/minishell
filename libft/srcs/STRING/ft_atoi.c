/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:19:04 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 15:11:45 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

#define INTMAX 2147483647
#define INTMIN 2147483648

static int	atoi_ret(int is_negative)
{
	if (is_negative == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				is_negative;
	unsigned int	nb;

	i = 0;
	is_negative = 1;
	nb = 0;
	while (((str[i] > 8 && str[i] < 14) || str[i] == 32) && str[i])
		i++;
	if ((str[i] == 43 || str[i] == 45) && str[i])
	{
		if (str[i] == 45)
			is_negative *= -1;
		i++;
	}
	while ((str[i] > 47 && str[i] < 58) && str[i])
	{
		nb *= 10;
		nb += str[i] - 48;
		if ((nb > INTMAX && is_negative == 1)
			|| (nb > INTMIN && is_negative == -1))
			return (atoi_ret(is_negative));
		i++;
	}
	return (nb * is_negative);
}
