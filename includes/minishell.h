/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:16:20 by jules             #+#    #+#             */
/*   Updated: 2021/04/13 13:57:11 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <termios.h>
# include <sys/types.h>
# include <signal.h>

# include "libft.h"
# include "constants.h"
# include "struct.h"

# include <curses.h>
# include <term.h>

/*
**	termcap/termcap.c
*/
int		init_termcap(t_termcap *tc);
int		read_bpb(char **input);

/*
**	termcap/term_mode.c
*/
void	change_term_mode(t_termcap *tc, int on);

/*
**	termcap/term_utils.c
*/
int		is_tckey(char tc[4], int const_tc);

/*
**	LEXER/lexer.c
*/
void	free_token(void *vtoken);
t_list	*tokenize_input(t_iter *iter);

/*
**	LEXER/lexer_get.c
*/
t_list	*get_quote(t_iter *iter);
t_list	*get_lchev(t_iter *iter);
t_list	*get_rchev(t_iter *iter);
t_list	*get_pipe(t_iter *iter);

/*
**	LEXER/lexer_dquote.c
*/
t_list	*get_dquote(t_iter *iter);

/*
**	LEXER/lexer_get2.c
*/
t_list	*get_semic(t_iter *iter);
t_list	*get_word(t_iter *iter);


/*
**	LEXER/lexer_utils.c
*/
t_token	*create_token(char *str, t_etype token);
char	*get_wbetw(size_t start, size_t end, char *line);
int		count_backslash(char *start);
void	lexer_free(t_list *root, t_iter *iter);

/*
**	ENV/pars_env
*/
void	disp_env(t_list *env);
void	free_envp(char **envp);
char	**get_envp(t_list *env);
char	*get_env_val(t_list *env, char *var);
void	mod_env(t_list **env, char *var, char *val);

/*
**	ENV/pars_env
*/
t_env	*create_env_elem(char *var, char *val);
void	del_env_elem(void *elem);
char	*get_var_from_str(char *str);
char	*get_val_from_str(char *str);
t_list	*pars_env(char **envp);


#endif
