/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:22:32 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/22 11:35:00 by jpeyron          ###   ########.fr       */
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
	SPACE,
	BASE
}				t_etype;

typedef struct	s_token
{
	t_etype		token;
	char		*str;
	bool		rm;
}				t_token;

typedef	struct	s_iter
{
	size_t		i;
	char		*err;
	char		*line;
}				t_iter;

typedef struct	s_spf
{
	char		spe;
	t_list		*(*f)(t_iter *iter);
}				t_spf;

typedef struct	s_termcap
{
	struct termios	o_termios;
}				t_termcap;

typedef struct	s_env
{
	char		*var;
	char		*val;
}				t_env;

typedef struct	s_termcaps
{
	int	col;
	int	curr_col;
	int	row;
	int	curr_row;
}				t_termcaps;


typedef struct	s_history
{
	t_list	*cmds;
	size_t	size;
	int		pos;
	int		fd;
}				t_history;

typedef struct	s_node
{
	t_etype	type;
	void	*node_t;
}				t_node;

typedef struct	s_ncommand
{
	char	*cmd;
	char	**args;
}				t_ncommand;

t_termcaps	g_tc;

#endif
