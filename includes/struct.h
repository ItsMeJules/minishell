/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:22:32 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:16:39 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_type
{
	QUOTE,
	D_QUOTE,
	PIPE,
	CHEV_R,
	CHEV_L,
	D_CHEV_R,
	SEMI,
	SPACE,
	BASE,
	FL,
	CMD,
	RDR
}				t_etype;

typedef struct s_token
{
	t_etype			token;
	char			*str;
	bool			rm;
}				t_token;

typedef struct s_iter
{
	size_t			i;
	char			*err;
	char			*line;
}				t_iter;

typedef struct s_spf
{
	char			spe;
	t_list			*(*f)(t_iter *iter);
}				t_spf;

typedef struct s_env
{
	char			*var;
	char			*val;
}					t_env;

typedef struct s_termcaps
{
	struct winsize	w;
	struct termios	o_termios;
	int				col;
	int				curr_col;
	int				row;
	int				curr_row;
	int				cursor_pos;
	t_list			*env;
	int				signal;
	int				forked;
}				t_termcaps;

typedef struct s_history
{	
	t_list			*cmds;
	size_t			size;
	int				pos;
	int				fd;
}				t_history;

typedef struct s_node
{
	t_list			*elem;
	t_etype			type;	
}				t_node;

typedef struct s_setup
{
	t_iter			*iter;
	t_list			*lexer;
	t_list			*vars;
	t_history		*history;
	t_btree			*ast;
	char			path[4096];
}				t_setup;

typedef struct s_exec
{
	int				fd_in;
	int				fd_out;
	int				in;
	int				out;
	bool			expand;
	char			*path;
	char			**av;
	char			**envp;
}				t_exec;

typedef struct s_cmd
{
	pid_t			pid[2];
	int				status[2];
	int				child_status;
	int				pfd[2];
}				t_cmd;

t_termcaps	g_tc;

#endif
