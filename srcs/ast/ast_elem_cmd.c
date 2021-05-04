/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_elem_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:20:54 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/04 11:03:02 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*skip_chev(t_list **elem)
{
	while (*elem->content->type != SPACE)
		*elem = *elem->next;
}

t_list	*next_command(t_list *lexer)
{
	static t_list	*elem = NULL;
	
	if (!elem)
		elem = lexer;
	else if (((t_token *)elem->content)->token == PIPE
			|| ((t_token *)elem->content)->token == SEMI)
		elem = elem->next;
	while (elem && ((t_token *)elem->content)->token != PIPE
			&& ((t_token *)elem->content)->token != SEMI)
	{
		while (is_chev((t_token *)elem->content->token))
			skip_chev(&elem);
		//echo lol>19 -n ; cat 1 > 2 >> 3 -n | touch 2 -t   
		//
		//>1>>2 echo lol<4 -n
		
		//__
	}
}
