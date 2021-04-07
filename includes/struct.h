/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:22:32 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/07 15:03:01 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum	e_type
{
	QUOTE,
	D_QUOTE,
	PIPE,
	CHEV_R,
	CHEV_L,
	D_CHEV_R,
	SEMI,
	BASE
}				t_etype;

typedef struct	s_token
{
	t_etype		token;
	char		*str;
}				t_token;

typedef	struct	s_iter
{
	size_t		i;
	size_t		err;
	char		*line;
}				t_iter;

typedef struct	s_spf
{
	char		spe;
	t_list		*(*f)(t_iter *iter);
}				t_spf;

#endif
