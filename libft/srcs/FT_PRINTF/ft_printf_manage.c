/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:21:59 by tvachera          #+#    #+#             */
/*   Updated: 2020/11/30 17:26:41 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	manage_char(t_print print, int c)
{
	int		size;

	if (print.justif.active != L_JUSTIF && print.pad.active == TRUE
		&& print.pad.width > 1)
	{
		size = print_c(print.pad.width - 1, '0');
		size += write(1, &c, 1);
	}
	else if (print.justif.active == L_JUSTIF && print.justif.width > 1)
	{
		size = write(1, &c, 1);
		size += print_c(print.justif.width - 1, ' ');
	}
	else if ((print.pad.active == TRUE && print.precis.active == TRUE
		&& print.pad.width > 1) || (print.justif.active == R_JUSTIF
		&& print.pad.active == FALSE && print.justif.width > 1))
	{
		size = print_c(print.pad.active == TRUE ? print.pad.width - 1
			: print.justif.width - 1, ' ');
		size += write(1, &c, 1);
	}
	else
		size = write(1, &c, 1);
	return (size < 0 ? 1 : size);
}

int	manage_str(t_print print, char *str)
{
	int		size;
	char	*ret;

	if (print.precis.active == TRUE)
		size = print.precis.width;
	else
		size = ft_strlen(str);
	if (!(ret = strndup2(str, size, print.precis.active)))
		return (0);
	if (print.justif.active != L_JUSTIF && print.pad.active == TRUE
		&& print.pad.width > ft_strlen(ret))
		ret = ret ? add_pad(ret, print.pad.width) : 0;
	if (print.justif.active == L_JUSTIF && print.justif.width > ft_strlen(ret))
		ret = ret ? add_left_justif(ret, print.justif.width) : 0;
	else if (print.pad.active == TRUE && print.precis.active == TRUE
		&& print.pad.width > ft_strlen(ret))
		ret = ret ? add_right_justif(ret, print.pad.width) : 0;
	else if (print.justif.active == R_JUSTIF && print.pad.active == FALSE
		&& print.justif.width > ft_strlen(ret))
		ret = ret ? add_right_justif(ret, print.justif.width) : 0;
	size = ret ? write(1, ret, ft_strlen(ret)) : 0;
	ret ? free(ret) : 0;
	return (size);
}

int	manage_signed(t_print print, long long nb, int size)
{
	char	*ret;

	if (print.precis.active == TRUE && print.precis.width == 0 && nb == 0)
		ret = get_empty_line();
	else
		ret = ft_unsigned_itoa_base(nb < 0 ? nb * -1 : nb, BASE_DECI);
	if (print.precis.active == TRUE && print.precis.width > ft_strlen(ret))
		ret = ret ? add_pad(ret, print.precis.width) : 0;
	else if (print.justif.active != L_JUSTIF && print.precis.active == FALSE
		&& print.pad.active == TRUE && print.pad.width > ft_strlen(ret))
		ret = ret ? add_pad(ret, print.pad.width) : 0;
	if (print.f_plus == TRUE || print.f_space == TRUE || nb < 0)
		ret = ret ? add_flags(print, ret, nb < 0) : 0;
	if (print.justif.active == L_JUSTIF && print.justif.width > ft_strlen(ret)
		&& print.ignore == FALSE)
		ret = ret ? add_left_justif(ret, print.justif.width) : 0;
	else if (print.pad.active == TRUE && print.precis.active == TRUE
		&& print.pad.width > ft_strlen(ret))
		ret = ret ? add_right_justif(ret, print.pad.width) : 0;
	else if (print.justif.active == R_JUSTIF && print.pad.active == FALSE
		&& print.justif.width > ft_strlen(ret))
		ret = ret ? add_right_justif(ret, print.justif.width) : 0;
	size = ret ? write(1, ret, ft_strlen(ret)) : 0;
	ret ? free(ret) : 0;
	return (size);
}

int	manage_unsigned(t_print print, unsigned long long nb)
{
	int		size;
	char	*ret;

	if (print.precis.active == TRUE && print.precis.width == 0 && nb == 0)
		ret = get_empty_line();
	else
		ret = ft_unsigned_itoa_base(nb, BASE_DECI);
	if (print.precis.active == TRUE && print.precis.width > ft_strlen(ret))
		ret = ret ? add_pad(ret, print.precis.width) : 0;
	else if (print.justif.active != L_JUSTIF && print.precis.active == FALSE
		&& print.pad.active == TRUE && print.pad.width > ft_strlen(ret))
		ret = ret ? add_pad(ret, print.pad.width) : 0;
	if (print.justif.active == L_JUSTIF && print.justif.width > ft_strlen(ret))
		ret = ret ? add_left_justif(ret, print.justif.width) : 0;
	else if (print.pad.active == TRUE && print.precis.active == TRUE
		&& print.pad.width > ft_strlen(ret))
		ret = ret ? add_right_justif(ret, print.pad.width) : 0;
	else if (print.justif.active == R_JUSTIF && print.pad.active == FALSE
		&& print.justif.width > ft_strlen(ret))
		ret = ret ? add_right_justif(ret, print.justif.width) : 0;
	size = ret ? write(1, ret, ft_strlen(ret)) : 0;
	ret ? free(ret) : 0;
	return (size);
}

int	manage_hex(t_print print, unsigned long long nb, int size)
{
	char	*ret;

	if (print.precis.active == TRUE && print.precis.width == 0 && nb == 0)
		ret = get_empty_line();
	else
		ret = print.specifier != 'X' ? ft_unsigned_itoa_base(nb, BASE_MINHEX)
		: ft_unsigned_itoa_base(nb, BASE_MAJHEX);
	if (print.precis.active == TRUE && print.precis.width > ft_strlen(ret))
		ret = ret ? add_pad(ret, print.precis.width) : 0;
	else if (print.justif.active != L_JUSTIF && print.precis.active == FALSE
		&& print.pad.active == TRUE && print.pad.width > ft_strlen(ret))
		ret = ret ? add_pad(ret, print.pad.width) : 0;
	if ((nb > 0 && print.f_hashtag == TRUE) || print.specifier == 'p')
		ret = ret ? add_f_hashtag(print, ret) : 0;
	if (print.justif.active == L_JUSTIF && print.justif.width > ft_strlen(ret))
		ret = ret ? add_left_justif(ret, print.justif.width) : 0;
	else if (print.pad.active == TRUE && print.precis.active == TRUE
		&& print.pad.width > ft_strlen(ret))
		ret = ret ? add_right_justif(ret, print.pad.width) : 0;
	else if (print.justif.active == R_JUSTIF && print.pad.active == FALSE
		&& print.justif.width > ft_strlen(ret))
		ret = ret ? add_right_justif(ret, print.justif.width) : 0;
	size = ret ? write(1, ret, ft_strlen(ret)) : 0;
	ret ? free(ret) : 0;
	return (size);
}
