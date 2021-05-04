/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 16:02:18 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/03 15:30:01 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*next_sep(t_list *lexer)
{
	static t_list	*elem = NULL;
	static bool		end = false;
	t_token			*token;

	if (end)
		return (NULL);
	if (!elem)
		elem = lexer;
	else
		elem = elem->next;
	while (elem)
	{
		token = (t_token *)elem->content;
		if (token->token == SEMI)
		{
			token->rm = true;
			return (elem);
		}
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
		return (NULL);
	if (!elem)
		elem = lexer;
	else
		elem = elem->next;
	while (elem && ((t_token *)elem->content)->token != SEMI)
	{
		token = (t_token *)elem->content;
		if (token->token == PIPE)
		{
			token->rm = true;
			return (elem);
		}
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
		return (NULL);
	if (!elem)
		elem = lexer;
	else
		elem = elem->next;
	while (elem && ((t_token *)elem->content)->token != PIPE
			&& ((t_token *)elem->content)->token != SEMI)
	{
		token = (t_token *)elem->content;
		if (is_chev(token->token))
		{
			token->rm = true;
			return (elem);
		}
		elem = elem->next;
	}
	if (!elem)
		end = true;
	return (NULL);
}

t_list	*next_file(t_list *lexer)
{
	((t_token *)lexer->next)->rm = true;
	return (lexer->next);
}
