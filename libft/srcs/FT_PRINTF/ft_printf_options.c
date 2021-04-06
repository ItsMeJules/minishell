/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_options.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:31:35 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/29 20:06:01 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*add_pad(char *nbr, size_t width)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = ft_strlen(nbr);
	j = 0;
	if (!(str = malloc(sizeof(char) * (width + 1))))
		return (0);
	while (i++ < width)
		str[j++] = '0';
	i = 0;
	while (nbr[i])
		str[j++] = nbr[i++];
	str[j] = 0;
	free(nbr);
	return (str);
}

char	*add_flags(t_print print, char *nbr, short is_neg)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 1;
	i = 1;
	if (print.pad.active == TRUE && print.precis.active == FALSE
		&& print.pad.width == ft_strlen(nbr) && nbr[0] == '0')
		i = 0;
	if (!(str = malloc(sizeof(char) * (ft_strlen(nbr) + i + 1))))
		return (0);
	if (is_neg)
		str[0] = '-';
	else if (print.f_plus == TRUE)
		str[0] = '+';
	else
		str[0] = ' ';
	i = i == 1 ? 0 : 1;
	while (nbr[i])
		str[j++] = nbr[i++];
	str[j] = 0;
	free(nbr);
	return (str);
}

char	*add_f_hashtag(t_print print, char *nbr)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 2;
	if (print.pad.active == TRUE && print.precis.active == FALSE
		&& print.pad.width == ft_strlen(nbr))
	{
		while (nbr[i] == '0' && i < 2)
			i++;
	}
	if (!(str = malloc(sizeof(char) * (ft_strlen(nbr) + (2 - i) + 1))))
		return (0);
	str[0] = '0';
	str[1] = print.specifier == 'X' ? 'X' : 'x';
	while (nbr[i])
		str[j++] = nbr[i++];
	str[j] = 0;
	free(nbr);
	return (str);
}

char	*add_left_justif(char *nbr, size_t width)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(str = malloc(sizeof(char) * (width + 1))))
		return (0);
	while (nbr[i])
		str[j++] = nbr[i++];
	while (j < width)
		str[j++] = ' ';
	str[j] = 0;
	free(nbr);
	return (str);
}

char	*add_right_justif(char *nbr, size_t width)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = ft_strlen(nbr);
	j = 0;
	if (!(str = malloc(sizeof(char) * (width + 1))))
		return (0);
	while (i++ < width)
		str[j++] = ' ';
	i = 0;
	while (nbr[i])
		str[j++] = nbr[i++];
	str[j] = 0;
	free(nbr);
	return (str);
}
