/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:35:16 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 12:14:14 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast_item(void *item)
{
	t_node	*node;

	node = (t_node *)item;
	ft_lstclear(&node->elem, free_token);
	free(node);
}

void	fix_ast_chain(void *item)
{
	t_node	*node;
	t_list	*lst;

	node = (t_node *)item;
	lst = node->elem;
	if (node->type != CMD && node->type != FL)
		lst->next = 0;
	else if (node->type == FL)
	{
		while (lst->next && is_strenum(((t_token *)lst->next->content)->token))
			lst = lst->next;
		lst->next = 0;
	}
	else
	{
		while (lst->next && (is_strenum(((t_token *)lst->next->content)->token)
			|| ((t_token *)lst->next->content)->token == SPACE))
			lst = lst->next;
		lst->next = 0;
	}
}

void	move_pipes_to_ast(t_btree **root, t_list *lexer)
{
	t_list	*new;

	while ((new = next_pipe(lexer)))
	{
		add_node(root, create_node(new, PIPE));
		while ((new = next_redir(lexer)))
		{
			add_node(root, create_node(new, RDR));
			add_node(root, create_node(new->next, FL));
		}
		if ((new = next_command(lexer)))
			add_node(root, create_node(new, CMD));
	}
}

t_btree	*parse_ast(t_list *lexer)
{
	t_btree	*root;
	t_list	*new;

	root = NULL;
	while (42)
	{
		if ((new = next_sep(lexer)))
			add_node(&root, create_node(new, SEMI));
		move_pipes_to_ast(&root, lexer);
		while ((new = next_redir(lexer)))
		{
			add_node(&root, create_node(new, RDR));
			add_node(&root, create_node(new->next, FL));
		}
		if ((new = next_command(lexer)))
			add_node(&root, create_node(new, CMD));
		else
			break ;
	}
	reset_builders();
	btree_apply_prefix(root, fix_ast_chain);
	return (root);
}
