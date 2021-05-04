/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_elem_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:20:54 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/04 12:04:28 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_chev(t_list *elem)
{
	while (((t_token *)elem->content)->token != SPACE)
		elem = elem->next;
}

void	link_all_args(t_list *elem)
{
	t_list	*end_cmd;

	while (elem && (((t_token *)elem->content)->token == SPACE
			|| is_strenum(((t_token *)elem->content)->token)))
		elem = elem->next;
	end_cmd = elem;
	if (is_chev(((t_token *)elem->content)->token))
		skip_chev(elem);
	end_cmd->next = elem;
}

t_list	*next_command(t_list *lexer)
{
	static t_list	*elem = NULL;
	t_list			*start;
	
	if (!elem)
		elem = lexer;
	else if (((t_token *)elem->content)->token == PIPE
			|| ((t_token *)elem->content)->token == SEMI)
		elem = elem->next;
	else if (is_chev(((t_token *)elem->content)->token))
		skip_chev(elem);
	start = elem;
	link_all_args(elem);
	while (elem && ((t_token *)elem->content)->token != PIPE
			&& ((t_token *)elem->content)->token != SEMI)
		elem = elem->next;
	return (start);
}
// TESTS THEORIQUE
//echo lol > 1 -n |
//rm_spaces=echo lol>1 -n | cat haha
//=echo-> ->lol-> ->-n | cat haha

//echo lol > 1 ;
//rm_spaces=echo lol>1 ;
//=echo-> ->lol-> ->;
	
//> 1 >>2 echo mdr < 4 ;
//rm_spaces=>1>>2 echo mdr<4 ;
//= ->echo-> ->mdr-> ->;
