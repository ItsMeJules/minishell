/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:16:20 by jules             #+#    #+#             */
/*   Updated: 2021/05/04 14:44:31 by jules            ###   ########.fr       */
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
void		print_prompt(char *path);

/*
**	termcap/termcap_init.c
*/
void		change_term_mode(int on);
int			init_termcap();

/*
**	termcap/termcap.c
*/
int			read_bpb(char **input, t_history *history);

/*
**	termcap/termcap_utils.c
*/
int			is_tckey(char tc[4], int const_tc);
void		get_cursor_pos(void);
int			ft_putchar(int c);
void		rewrite_line(char *str, int col);

/*
** termcap/termcap_commands.c
*/
void		clear_after(int row, int col);
void		move_cursor(int row, int col);

/*
** termcap/input_editor.c
*/
int			add_input(char c, char **input);
void		handle_ctrld(char **input);
void		handle_backspace(char **input);

/*
**	termcap/input_cursor.c
*/
void		handle_cursor_move_left();
void		handle_cursor_move_right(char **input);
void		handle_up_arrow(t_history *history, char **input);
void		handle_down_arrow(t_history *history, char **input);

/*
**	LEXER/lexer.c
*/
void		free_token(void *vtoken);
t_list		*tokenize_input(t_iter *iter);

/*
**	LEXER/lexer_get.c
*/
t_list		*get_quote(t_iter *iter);
t_list		*get_lchev(t_iter *iter);
t_list		*get_rchev(t_iter *iter);
t_list		*get_pipe(t_iter *iter);

/*
**	LEXER/lexer_dquote.c
*/
t_list		*get_dquote(t_iter *iter);

/*
**	LEXER/lexer_get2.c
*/
t_list		*get_semic(t_iter *iter);
t_list		*get_word(t_iter *iter);

/*
**	LEXER/lexer_utils.c
*/
t_token		*create_token(char *str, t_etype token);
char		*get_wbetw(size_t start, size_t end, char *line);
int			count_backslash(char *start);
void		lexer_free(t_list *root, t_iter *iter);

/*
**	LEXER/check.c
*/
void		disp_error(char *str);
bool		check_chev(t_list *lexer);
bool		check_pipe(t_list *lexer, int i);
bool		check_parsing(t_list *lexer);

/*
**	ENV/mod_env.c
*/
void		disp_env(t_list *env);
void		free_envp(char **envp);
char		**get_envp(t_list *env);
char		*get_env_val(t_list *env, char *var);
void		mod_env(t_list **env, char *var, char *val);

/*
**	ENV/pars_env.c
*/
t_env		*create_env_elem(char *var, char *val);
void		del_env_elem(void *elem);
char		*get_var_from_str(char *str);
char		*get_val_from_str(char *str);
t_list		*pars_env(char **envp);

/*
** 	EXP/expand.c
*/
bool		is_declaration(char *str);
bool		is_declaration_field(t_list *lexer);
void		add_vars(t_list *lexer, t_list **env, t_list **vars);
void		mark_useless_declarations(t_list *lexer);
void		expand(t_list **lexer, t_list **env, t_list **vars);

/*
** 	EXP/expand2.c
*/
int			is_removable(void *data1, void *data2);
void		split_for_expand(t_token *token, t_list **lst);
void		expand_split(t_list *split, t_list *env, t_list *vars, t_etype type);
void		expand_elem(t_list *lexer, t_list *env, t_list *vars);
void		expand_field(t_list *lexer, t_list *env, t_list *vars);

/*
** 	EXP/expand3.c
*/
void		lst_rmdspace(t_list **alst);
void		lst_rmdsemi(t_list **alst);
char		*expand_dsign(char *str, t_list *env, t_list *vars);
char		*expand_bslash(char *str, t_etype type);
char		*join_split(t_list *split);
/*
** 	EXP/expand4.c
*/
char		*join_declaration(char *str, t_token *token);
bool		is_strenum(t_etype type);
void		concat_chains(t_list *lexer);
void		lst_rmempty(t_list **alst);

/*
**	EXEC/path.c
*/
bool		is_var(t_list *list, char *var);
char		*join_path(char *path, char *bin);
char		*find_path(char **paths, char *bin);
char		*get_path(char *bin, t_list *env, t_list *vars);

/*
**	BUILTINS/env.c
*/
int			env(t_list *env);

/*
**	BUILTINS/export.c
*/
int			print_declare(t_list *env);
void		set_env(t_list **env, t_list **vars, char *var);
void		mod_env2(t_list **env, char *var, char *val);
void		remove_var(t_list **vars, char *var);
int			export(int argc, char **argv, t_list **env, t_list **vars);

/*
**	BUILTINS/unset.c
*/
int			unset_err(char *str);
int			unset(int argc, char **argv, t_list **env, t_list **vars);

/*
**	BUILTINS/echo.c
*/
int			ft_echo(int ac, char **av);

/*
**	history/file_manager.c
*/
t_history	*read_file(char *file);
int			save_command(char *command, t_history *history);
void		free_history(t_history *history);

/*
**	BUILTINS/pwd.c
*/
int			ft_pwd();

/*
**	AST/ast_elem.c
*/
t_list		*next_sep(t_list *lexer);
t_list		*next_pipe(t_list *lexer);
t_list		*next_redir(t_list *lexer);
t_list		*next_file(t_list *lexer);

/*
**	AST/ast_elem_cmd.c
*/
void		skip_chev(t_list *elem);
void		link_all_args(t_list *elem);
t_list		*next_command(t_list *lexer);

/*
**	AST/ast_parser.c
*/
void		disp_node(void *item); // A RETIRER
void		free_ast_item(void *item);
void		fix_ast_chain(void *item);
void		move_pipes_to_ast(t_btree **root, t_list *lexer);
t_btree		*parse_ast(t_list *lexer);

/*
**	AST/ast_building.c
*/
t_node		*create_node(t_list *elem, t_etype type);
bool		is_leaf(t_btree *leaf);
bool		add_node(t_btree **root, t_node *node);

/*
**	AST/ast_utils.c
*/
bool		is_chev(t_etype type);
void		rm_unused_spaces(t_list **lexer);

/*
**	BUILTINS/cd.c
*/
int			ft_cd(int ac, char **av, t_list *env);

#endif
