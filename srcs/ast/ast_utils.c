/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 16:14:30 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/30 17:45:22 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_chev(t_etype type)
{
	return (type == CHEV_R || type == D_CHEV_R || type == CHEV_L)
}

void	rm_unused_spaces(t_list **lexer)
{
	t_list	*elem;
	t_token	*token;

	elem = *lexer;
	if (((t_token *)elem->content)->token == SPACE)
		((t_token *)elem->content)->rm = true;
	while (elem)
	{
		token = (t_token *)elem->content;
		if (token->token == SPACE)
		{
			if (elem->next && !is_strenum(((t_token *)elem->next)->content))
				token->rm = true;	
			else if (!elem->next)
				token->rm = true;
		}
		elem = elem->next;
	}
	ft_lstremove_if(lexer, *lexer, is_removable, free_token);
}
