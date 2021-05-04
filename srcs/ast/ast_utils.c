/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 16:14:30 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/04 15:28:11 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_chev(t_etype type)
{
	return (type == CHEV_R || type == D_CHEV_R || type == CHEV_L);
}

bool	is_redir(t_etype type)
{
	return (is_chev(type) || type == PIPE);
}

void	rm_unused_spaces(t_list **lexer)
{
	t_list	*elem;
	t_list	*prev;
	t_token	*token;

	elem = *lexer;
	if (((t_token *)elem->content)->token == SPACE)
		((t_token *)elem->content)->rm = true;
	while (elem)
	{
		token = (t_token *)elem->content;
		if (token->token == SPACE)
		{
			if (elem->next && !is_strenum(((t_token *)elem->next->content)->token))
				token->rm = true;
			else if (!elem->next)
				token->rm = true;
			else if (prev && is_chev(((t_token *)prev->content)->token))
				token->rm = true;
		}
		prev = elem;
		elem = elem->next;
	}
	ft_lstremove_if(lexer, *lexer, is_removable, free_token);
}
