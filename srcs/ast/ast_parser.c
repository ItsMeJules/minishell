/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:35:16 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:12:01 by tvachera         ###   ########.fr       */
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

	new = next_pipe(lexer);
	while (new)
	{
		add_node(root, create_node(new, PIPE));
		new = next_redir(lexer);
		while (new)
		{
			add_node(root, create_node(new, RDR));
			add_node(root, create_node(new->next, FL));
			new = next_redir(lexer);
		}
		new = next_command(lexer);
		if (new)
			add_node(root, create_node(new, CMD));
		new = next_pipe(lexer);
	}
}

t_btree	*parse_ast(t_list *lexer)
{
	t_btree	*root;
	t_list	*new;

	root = NULL;
	while (42)
	{
		new = next_sep(lexer);
		if (new)
			add_node(&root, create_node(new, SEMI));
		move_pipes_to_ast(&root, lexer);
		new = next_redir(lexer);
		while (new)
		{
			add_node(&root, create_node(new, RDR));
			add_node(&root, create_node(new->next, FL));
			new = next_redir(lexer);
		}
		new = next_command(lexer);
		if (new)
			add_node(&root, create_node(new, CMD));
		else
			break ;
	}
	return (clean_building(root));
}
