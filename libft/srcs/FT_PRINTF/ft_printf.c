/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:19:08 by tvachera          #+#    #+#             */
/*   Updated: 2020/12/24 13:46:09 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		get_arg(va_list arg, const char *str, int size)
{
	t_print	print;

	print = set_print(arg, str);
	if (in_str(print.specifier, "di") == TRUE)
		return (convert_signed(arg, print));
	else if (print.specifier == 'n')
		convert_n(arg, print, size);
	else if (in_str(print.specifier, "uxXp") == TRUE)
		return (convert_unsigned(arg, print));
	else if (in_str(print.specifier, "sc%") == TRUE)
		return (convert_alpha(arg, print));
	return (0);
}

void	get_sub_specifiers(t_print *print, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && is_valid(str[i]) == TRUE && is_specifier(str[i]) == FALSE)
	{
		if (str[i] == 'h' && str[i - 1] != 'h' && str[i + 1] != 'h')
			print->sub_specifier < SUB_H ? print->sub_specifier = SUB_H : 0;
		else if (str[i] == 'h')
			print->sub_specifier < SUB_HH ? print->sub_specifier = SUB_HH : 0;
		if (str[i] == 'l' && str[i - 1] != 'l' && str[i + 1] != 'l')
			print->sub_specifier < SUB_L ? print->sub_specifier = SUB_L : 0;
		else if (str[i] == 'l')
		{
			print->sub_specifier = SUB_LL;
			return ;
		}
		i++;
	}
}

int		start(va_list arg, const char *str)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] && str[i] != '%')
			ret += get_word(str + i, &i);
		else if (str[i] && str[i] == '%')
		{
			ret += get_arg(arg, str + ++i, ret);
			while (str[i] && is_valid(str[i]) == TRUE
				&& is_specifier(str[i]) == FALSE)
				i++;
			str[i] ? i++ : 0;
		}
	}
	return (ret);
}

int		ft_printf(const char *str, ...)
{
	va_list	arg;
	int		ret;

	if (!str)
		return (0);
	va_start(arg, str);
	ret = start(arg, str);
	va_end(arg);
	return (ret);
}
