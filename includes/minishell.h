/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:16:20 by jules             #+#    #+#             */
/*   Updated: 2021/04/14 18:18:37 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <signal.h>

# include "libft.h"
# include "constants.h"
# include "struct.h"

# include <curses.h>
# include <term.h>

/*
**	termcap/termcap_init.c
*/
void	change_term_mode(t_termcap *tc, int on);
int		init_termcap(t_termcap *tc);

/*
**	termcap/termcap.c
*/
int		read_bpb(char **input);

/*
**	termcap/termcap_utils.c
*/
int		is_tckey(char tc[4], int const_tc);
void	get_cursor_pos(void);
int		ft_putchar(int c);
void	rewrite_line(char *str);

/*
** termcap/termcap_commands.c
*/
void	clear_after(int row, int col);
void	move_cursor(int row, int col);

/*
** termcap/cursor.c
*/
void	handle_cursor_move(int mode, char *input);
void	handle_backspace(char **input);

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


/*
**	history/file_manager.c
*/
t_history	*read_file(char *file);
int			save_command(char *command, t_history *history);

#endif
