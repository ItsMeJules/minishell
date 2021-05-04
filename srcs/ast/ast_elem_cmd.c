/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_elem_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:20:54 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/04 17:30:57 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*skip_chev(t_list *elem)
{
	if (!elem)
		return (NULL);
	if (is_chev(((t_token *)elem->content)->token))
		elem = elem->next;
	while (elem && is_strenum(((t_token *)elem->content)->token))
		elem = elem->next;
	if (elem && !is_chev(((t_token *)elem->content)->token))
		return (elem);
	return (skip_chev(elem));
}

void	init_elem(t_list *lexer, t_list **elem, t_list **start)
{
	if (!*elem)
		*elem = lexer;
	if (is_chev(((t_token *)(*elem)->content)->token))
		*start = skip_chev(*elem);
	else
		*start = *elem;
	*elem = *start;
}

t_list	*next_command(t_list *lexer)
{
	static t_list	*elem = NULL;
	static bool		end = false;
	t_list			*start;
	
	if (end)
	{
		elem = NULL;
		end = false;
		return (NULL);
	}
	init_elem(lexer, &elem, &start);
	while (elem && ((t_token *)elem->content)->token != PIPE
			&& ((t_token *)elem->content)->token != SEMI)
	{
		if (elem->next && is_chev(((t_token *)elem->next->content)->token))	
			elem->next = skip_chev(elem->next);
		elem = elem->next;
	}
	if (!elem)
		end = true;
	else
		elem = elem->next;
	return (start);
}
