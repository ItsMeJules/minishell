/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:15:01 by tvachera          #+#    #+#             */
/*   Updated: 2020/12/24 13:55:29 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define FALSE 0
# define TRUE 1
# define L_JUSTIF 1
# define R_JUSTIF 2
# define SUB_H 1
# define SUB_HH 2
# define SUB_L 3
# define SUB_LL 4
# define BASE_MINHEX "0123456789abcdef"
# define BASE_MAJHEX "0123456789ABCDEF"
# define BASE_DECI "0123456789"
# define SPECIFIERS "cspdiuxXnfge%"
# define VALID "0123456789-+ #*.hl"

typedef struct	s_precision
{
	short		active;
	size_t		width;
}				t_precision;

typedef struct	s_justify
{
	short		active;
	size_t		width;
}				t_justify;

typedef struct	s_pad
{
	short		active;
	size_t		width;
}				t_pad;

typedef struct	s_print
{
	char		specifier;
	short		sub_specifier;
	short		f_plus;
	short		f_space;
	short		f_hashtag;
	short		ignore;
	t_precision	precis;
	t_justify	justif;
	t_pad		pad;
}				t_print;

int				get_arg(va_list arg, const char *str, int size);
int				start(va_list arg, const char *str);
int				ft_printf(const char *str, ...);
void			get_sub_specifiers(t_print *print, const char *str);

char			**get_arg_widths(va_list arg, const char *str);
size_t			get_chain_size(char **tab, const char *str);
void			fill_chain(char **tab, const char *str, char *new);
char			*get_chain(va_list arg, const char *str);

int				manage_char(t_print print, int c);
int				manage_str(t_print print, char *str);
int				manage_signed(t_print print, long long nb, int size);
int				manage_unsigned(t_print print, unsigned long long nb);
int				manage_hex(t_print print, unsigned long long nb, int size);

char			*add_pad(char *nbr, size_t width);
char			*add_flags(t_print print, char *nbr, short is_neg);
char			*add_f_hashtag(t_print print, char *nbr);
char			*add_left_justif(char *nbr, size_t width);
char			*add_right_justif(char *nbr, size_t width);

int				convert_signed(va_list arg, t_print print);
int				convert_unsigned(va_list arg, t_print print);
int				convert_double(va_list arg, t_print print);
int				convert_alpha(va_list arg, t_print print);
void			convert_n(va_list arg, t_print print, int size);

void			get_pad(const char *str, t_print *print, va_list arg);
void			get_justification(const char *str, t_print *print, va_list arg);
void			get_precision(const char *str, t_print *print, va_list arg);
void			get_flags(t_print *print, const char *str, va_list arg);
t_print			set_print(va_list arg, const char *str);

long			ft_atoi_lg(const char *str);
short			in_str(char c, const char *str);
int				print_c(size_t width, char c);

int				get_nb_len(unsigned long long nb, unsigned long long *pow,
				unsigned short base_len);
char			*ft_itoa_base(long long n, char *base);
char			*ft_unsigned_itoa_base(unsigned long long n, char *base);
short			is_valid(char c);
short			is_specifier(char c);

char			*get_empty_line(void);
char			*strndup2(const char *s1, size_t n, short active);
size_t			get_decim_len(double d);
int				get_word(const char *str, size_t *index_str);

#endif
