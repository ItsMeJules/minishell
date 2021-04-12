/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:16:20 by jules             #+#    #+#             */
/*   Updated: 2021/04/12 13:15:29 by jules            ###   ########.fr       */
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
** termcap.c
*/
int		init_termcap(t_termcap *tc);
int		read_bpb(char **input);

/*
** term_mode.c
*/
void	change_term_mode(t_termcap *tc, int on);

/*
** lexer.c
*/
void	free_token(void *vtoken);
t_list	*tokenize_input(t_iter *iter);

/*
** lexer_get.c
*/
t_list	*get_quote(t_iter *iter);
t_list	*get_lchev(t_iter *iter);
t_list	*get_rchev(t_iter *iter);
t_list	*get_pipe(t_iter *iter);

/*
** lexer_dquote.c
*/
t_list	*get_dquote(t_iter *iter);

/*
** lexer_get2.c
*/
t_list	*get_semic(t_iter *iter);
t_list	*get_word(t_iter *iter);


/*
** lexer_utils.c
*/
t_token	*create_token(char *str, t_etype token);
char	*get_wbetw(size_t start, size_t end, char *line);
int		count_backslash(char *start);
void	lexer_free(t_list *root, t_iter *iter);

#endif
