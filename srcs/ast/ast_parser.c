/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:39:16 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/22 16:54:30 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_left_command(t_root *root)
{
	if (((t_node *)root->left)->type != COMMAND)	
		return (find_left_command(root->left));
	if (is_redir(((t_node *)root)->type))
}

void	add_node(t_btree **root, t_node *node)
{
	if (!(*root))
	{
		*root = btree_create_node(node);
		return ;
	}

}
//echo lol | cat ; touch hi | < lol ; echo haha > 3
t_btree	*parse_ast(t_list *lexer)
{
	t_btree		*root;
	t_node		*new;
	
	root = NULL;
	while (42)
	{
		if ((new = next_sep(lexer)))
			add_node(&root, new);
		while ((new = next_redir(lexer)))
		{
			add_node(&root, new);
			if (new->type == PIPE)
				add_node(cmd_pipe(lexer));
			else
				add_node(get_file(lexer));
		}
		if ((new = get_cmd(lexer)))
			add_node(&root, new);
		else
			return (root);
	}
}

//echo test | cat > 1 -b ; cat main.c
