/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:16:20 by jules             #+#    #+#             */
/*   Updated: 2021/04/20 17:21:36 by jpeyron          ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>

# include "libft.h"
# include "constants.h"
# include "struct.h"

# include <curses.h>
# include <term.h>

/*
** main.c
*/
void	print_prompt(void);

/*
**	termcap/termcap_init.c
*/
void	change_term_mode(int on);
int		init_termcap();

/*
**	termcap/termcap.c
*/
int		read_bpb(char **input, t_history *history);

/*
**	termcap/termcap_utils.c
*/
int		is_tckey(char tc[4], int const_tc);
void	get_cursor_pos(void);
int		get_rel_col(void);
int		ft_putchar(int c);
void	rewrite_line(char *str, int col);

/*
** termcap/termcap_commands.c
*/
void	clear_after(int row);
void	move_cursor(int row, int col);

/*
** termcap/cursor.c
*/
void	handle_cursor_move(int mode, char **input, t_history *history);
void	handle_backspace(char **input);

/*
**	termcap/cursor_lr.c
*/
void	handle_cursor_move_left();
void	handle_cursor_move_right(char **input);

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
**	ENV/mod_env.c
*/
void	disp_env(t_list *env);
void	free_envp(char **envp);
char	**get_envp(t_list *env);
char	*get_env_val(t_list *env, char *var);
void	mod_env(t_list **env, char *var, char *val);

/*
**	ENV/pars_env.c
*/
t_env	*create_env_elem(char *var, char *val);
void	del_env_elem(void *elem);
char	*get_var_from_str(char *str);
char	*get_val_from_str(char *str);
t_list	*pars_env(char **envp);

/*
** 	EXP/expand.c
*/
bool	is_declaration(char *str);
bool	is_declaration_field(t_list *lexer);
void	add_vars(t_list *lexer, t_list **env, t_list **vars);
void	mark_useless_declarations(t_list *lexer);
void	expand(t_list **lexer, t_list **env, t_list **vars);

/*
** 	EXP/expand2.c
*/
int		is_removable(void *data1, void *data2);
void	split_for_expand(t_token *token, t_list **lst);
void	expand_split(t_list *split, t_list *env, t_list *vars, t_etype type);
void	expand_elem(t_list *lexer, t_list *env, t_list *vars);
void	expand_field(t_list *lexer, t_list *env, t_list *vars);

/*
** 	EXP/expand3.c
*/
void	lst_rmdspace(t_list **alst);
void	lst_rmdsemi(t_list **alst);
char	*expand_dsign(char *str, t_list *env, t_list *vars);
char	*expand_bslash(char *str, t_etype type);
char	*join_split(t_list *split);
/*
** 	EXP/expand4.c
*/
char	*join_declaration(char *str, t_token *token);
bool	is_strenum(t_etype type);
void	concat_chains(t_list *lexer);

/*
**	EXEC/path.c
*/
bool	is_var(t_list *list, char *var);
char	*join_path(char *path, char *bin);
char	*find_path(char **paths, char *bin);
char	*get_path(char *bin, t_list *env, t_list *vars);

/*
**	history/file_manager.c
*/
t_history	*read_file(char *file);
int			save_command(char *command, t_history *history);
void		free_history(t_history *history);

#endif
