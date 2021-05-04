/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 16:02:18 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/04 17:30:09 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*next_sep(t_list *lexer)
{
	static t_list	*elem = NULL;
	static bool		end = false;
	t_token			*token;

	if (end)
	{
		elem = NULL;
		end = false;
		return (NULL);
	}
	if (!elem)
		elem = lexer;
	else
		elem = elem->next;
	while (elem)
	{
		token = (t_token *)elem->content;
		if (token->token == SEMI)
			return (elem);
		elem = elem->next;
	}
	end = true;
	return (NULL);
}

t_list	*next_pipe(t_list *lexer)
{
	static t_list	*elem = NULL;
	static bool		end = false;
	t_token			*token;

	if (end)
	{
		elem = NULL;
		end = false;
		return (NULL);
	}
	if (!elem)
		elem = lexer;
	else
		elem = elem->next;
	while (elem && ((t_token *)elem->content)->token != SEMI)
	{
		token = (t_token *)elem->content;
		if (token->token == PIPE)
			return (elem);
		elem = elem->next;
	}
	if (!elem)
		end = true;
	return (NULL);
}

t_list	*next_redir(t_list *lexer)
{
	static t_list	*elem = NULL;
	static bool		end = false;
	t_token			*token;

	if (end)
	{
		elem = NULL;
		end = false;
		return (NULL);
	}
	if (!elem)
		elem = lexer;
	else
		elem = elem->next;
	while (elem && ((t_token *)elem->content)->token != PIPE
			&& ((t_token *)elem->content)->token != SEMI)
	{
		token = (t_token *)elem->content;
		if (is_chev(token->token))
			return (elem);
		elem = elem->next;
	}
	if (!elem)
		end = true;
	return (NULL);
}
