/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_t_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:47:37 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/30 17:16:36 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	get_pad(const char *str, t_print *print, va_list arg)
{
	int	width;

	print->pad.active = TRUE;
	if (str[0] == '*')
	{
		width = va_arg(arg, int);
		if (width < 0)
		{
			print->justif.active = L_JUSTIF;
			width * -1 > (int)print->justif.width
				? print->justif.width = width * -1 : 0;
		}
		else
			print->pad.width = width;
	}
	else
		print->pad.width = ft_atoi_lg(str);
	if (print->justif.active == L_JUSTIF && print->pad.width
		> print->justif.width)
		print->justif.width = print->pad.width;
}

void	get_justification(const char *str, t_print *print, va_list arg)
{
	int			width;

	if (ft_isdigit(str[0]) == TRUE || str[0] == '*')
		print->justif.active = R_JUSTIF;
	else
	{
		print->justif.active = L_JUSTIF;
		str++;
	}
	if (str[0] == '*')
	{
		width = va_arg(arg, int);
		width < 0 ? print->justif.active = L_JUSTIF : 0;
		width < 0 && width * -1 > (int)print->justif.width ?
			print->justif.width = width * -1 : 0;
		width >= 0 ? print->justif.width = width : 0;
	}
	else
		print->justif.width = ft_atoi_lg(str);
	if (print->pad.active == TRUE)
		print->pad.width = print->justif.width;
}

void	get_precision(const char *str, t_print *print, va_list arg)
{
	int			width;

	print->precis.active = TRUE;
	if (str[0] == '*')
	{
		width = va_arg(arg, int);
		if (width < 0)
		{
			print->justif.active = L_JUSTIF;
			width * -1 > (int)print->justif.width
				? print->justif.width = width * -1 : 0;
			print->precis.active = FALSE;
			print->ignore = TRUE;
		}
		else
			print->precis.width = width;
	}
	else if (ft_atoi_lg(str) > 0)
		print->precis.width = ft_atoi_lg(str);
	else
		print->precis.width = 0;
}

void	get_flags(t_print *print, const char *str, va_list arg)
{
	size_t	i;

	i = 0;
	while (str[i] && is_valid(str[i]) == TRUE && is_specifier(str[i]) == FALSE)
	{
		if (str[i] == '+')
			print->f_plus = TRUE;
		else if (str[i] == ' ')
			print->f_space = TRUE;
		else if (str[i] == '#')
			print->f_hashtag = TRUE;
		else if (str[i] == '0' && str[i - 1] != '.' && str[i - 1] != '-'
			&& ft_isdigit(str[i - 1]) == FALSE)
			get_pad(str + i + 1, print, arg);
		else if (str[i] == '-' || (ft_isdigit(str[i]) && str[i - 1] != '-'
			&& ft_isdigit(str[i - 1]) == FALSE && str[i - 1] != '.'
			&& str[i] != '0' && print->justif.active != L_JUSTIF)
			|| (str[i] == '*' && (i == 0 || in_str(str[i - 1], " +#"))))
			get_justification(str + i, print, arg);
		else if (str[i] == '.')
			get_precision(str + i + 1, print, arg);
		i++;
	}
	if (is_specifier(str[i]) == TRUE)
		print->specifier = str[i];
}

t_print	set_print(va_list arg, const char *str)
{
	t_print	new;

	new.specifier = 0;
	new.sub_specifier = 0;
	new.f_plus = FALSE;
	new.f_space = FALSE;
	new.f_hashtag = FALSE;
	new.precis.active = FALSE;
	new.precis.width = 0;
	new.justif.active = FALSE;
	new.justif.width = 0;
	new.pad.active = FALSE;
	new.pad.width = 0;
	new.ignore = FALSE;
	get_flags(&new, str, arg);
	get_sub_specifiers(&new, str);
	return (new);
}
