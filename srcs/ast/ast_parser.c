/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:39:16 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/27 16:44:33 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_btree **root, t_list *node)
{
	if (!(*root))
	{
		*root = btree_create_node(node);
		return ;
	}
	if (!(*root)->left)
		(*root)->left = btree_create_node(node);
	else if (!(*root)->right)
		(*root)->right = btree_create_node(node);
	else
		add_node(&(*root)->right, node);
}

t_redir	*new_redir(t_etype type, char *file)
{
	t_redir	*new;

	if (!(new = malloc(sizeof(t_redir))))
		return (NULL);
	new->type = type;
	new->file = file;
	return (new);
}

t_list	*get_redirs(t_list	*lexer)
{
	t_list	*redirs;
	t_redir	*new;

	redirs = NULL;
	while (lexer && ((t_token *)lexer->content)->token != PIPE
			&& ((t_token *)lexer->content)->token != SEMI)
	{
		while (lexer && ((t_token *)lexer->content)->token != PIPE
			&& ((t_token *)lexer->content)->token != SEMI
			&& !is_redir(((t_token *)lexer->content)->token))
			lexer = lexer->next;
		if (lexer && is_redir(((t_token *)lexer->content)->token))
		{
			new = new_redir(((t_token *)lexer->content)->token
				, ft_strdup(((t_token *)lexer->next->content)->str));
			ft_lstadd_back(&redirs, ft_lstnew(new));
			lexer = lexer->next->next;
		}
	}
	return (redirs);
}

t_list	*create_leaf(t_list *lexer)
{
	t_list	*pipes;
	t_node	*new;

	pipes = NULL;
	while (lexer && ((t_token *)lexer->content)->token != SEMI)
	{
		new = new_node(true, fill_argv(lexer, nb_words(lexer))
			, get_redirs(lexer));
		ft_lstadd_back(&pipes, ft_lstnew(new));
		while (lexer && ((t_token *)lexer->content)->token != PIPE
			&& ((t_token *)lexer->content)->token != SEMI)
			lexer = lexer->next;
		if (lexer && ((t_token *)lexer->content)->token == PIPE)
			lexer = lexer->next;
	}
	return (pipes);
}

t_btree	*parse_ast(t_list *lexer)
{
	t_btree	*root;
	t_list	*node;

	root = NULL;
	while (lexer && (node = next_sep(lexer)))
	{
		add_node(&root, node);
		add_node(&root, create_leaf(lexer));
		while (lexer && ((t_token *)lexer->content)->token != SEMI)
			lexer = lexer->next;
		if (lexer)
			lexer = lexer->next;
	}
	add_node(&root, create_leaf(lexer));
	return (root);
}
