/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:41:11 by tvachera          #+#    #+#             */
/*   Updated: 2020/12/24 13:38:37 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		convert_signed(va_list arg, t_print print)
{
	if (print.sub_specifier == SUB_H)
		return (manage_signed(print, (short)va_arg(arg, long), 0));
	else if (print.sub_specifier == SUB_HH)
		return (manage_signed(print, (char)va_arg(arg, long), 0));
	else if (print.sub_specifier == SUB_L)
		return (manage_signed(print, va_arg(arg, long), 0));
	else if (print.sub_specifier == SUB_LL)
		return (manage_signed(print, va_arg(arg, long long), 0));
	else
		return (manage_signed(print, va_arg(arg, int), 0));
}

int		convert_unsigned(va_list arg, t_print print)
{
	if (print.specifier == 'p')
		return (manage_hex(print, va_arg(arg, unsigned long long), 0));
	else if (print.sub_specifier == SUB_H)
		return (print.specifier != 'u'
			? manage_hex(print, (unsigned short)va_arg(arg, unsigned int), 0)
			: manage_unsigned(print, (unsigned short)va_arg(arg
			, unsigned int)));
	else if (print.sub_specifier == SUB_HH)
		return (print.specifier != 'u'
			? manage_hex(print, (unsigned char)va_arg(arg, unsigned int), 0)
			: manage_unsigned(print, (unsigned char)va_arg(arg
			, unsigned int)));
	else if (print.sub_specifier == SUB_L)
		return (print.specifier != 'u'
			? manage_hex(print, va_arg(arg, unsigned long), 0)
			: manage_unsigned(print, va_arg(arg, unsigned long)));
	else if (print.sub_specifier == SUB_LL)
		return (print.specifier != 'u'
			? manage_hex(print, va_arg(arg, unsigned long long), 0)
			: manage_unsigned(print, va_arg(arg, unsigned long long)));
	else
		return (print.specifier != 'u'
			? manage_hex(print, va_arg(arg, unsigned int), 0)
			: manage_unsigned(print, va_arg(arg, unsigned int)));
}

int		convert_alpha(va_list arg, t_print print)
{
	if (print.specifier == '%')
		return (manage_char(print, '%'));
	else if (print.specifier == 's' && print.sub_specifier == SUB_L)
		return (manage_str(print, (char *)va_arg(arg, wchar_t *)));
	else if (print.specifier == 's')
		return (manage_str(print, (char *)va_arg(arg, int *)));
	else
		return (manage_char(print, va_arg(arg, int)));
}

void	convert_n(va_list arg, t_print print, int size)
{
	if (print.sub_specifier == SUB_H)
		*(va_arg(arg, short *)) = (short)size;
	else if (print.sub_specifier == SUB_HH)
		*(va_arg(arg, char *)) = (char)size;
	else if (print.sub_specifier == SUB_L)
		*(va_arg(arg, long *)) = (long)size;
	else if (print.sub_specifier == SUB_LL)
		*(va_arg(arg, long long *)) = (long long)size;
	else
		*(va_arg(arg, int *)) = size;
}
