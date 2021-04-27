/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:55:13 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/27 16:32:51 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(void *to_free)
{
	t_redir	*redir;

	redir = (t_redir *)to_free;
	free(redir->file);
	free(redir);
}

void	free_node(void *to_free)
{
	t_node	*node;

	node = (t_node *)to_free;
	if (node->leaf)
	{
		ft_free_split(node->argv);
		ft_lstclear(&node->redirs, free_redirs);
	}
	free(node);
}

void	free_ast_elem(void *to_free)
{
	t_list	*lst;

	lst = (t_list *)to_free;
	ft_lstclear(&lst, free_node);
}
