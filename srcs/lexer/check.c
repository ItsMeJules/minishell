/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:37:38 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 11:44:03 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disp_error(char *str)
{
	write(2, TERM_NAME, ft_strlen(TERM_NAME));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
}

bool	check_chev(t_list *lexer)
{
	lexer = lexer->next;
	while (lexer && ((t_token *)lexer->content)->token != SEMI)
	{
		if (is_strenum(((t_token *)lexer->content)->token))
			return (true);
		else if (((t_token *)lexer->content)->token != SPACE)
			return (false);
		lexer = lexer->next;
	}
	return (false);
}

bool	check_pipe(t_list *lexer, int i)
{
	t_list	*elem;

	if (!i)
		return (false);
	else if (!ft_lstat(lexer, i + 1))
		return (false);
	i--;
	elem = ft_lstat(lexer, i);
	while (i >= 0 && ((t_token *)elem->content)->token != SEMI && elem->next)
	{
		if (is_strenum(((t_token *)elem->content)->token))
			return (true);
		else if (((t_token *)elem->content)->token != SPACE)
			return (false);
		i--;
		if (i >= 0)
			elem = ft_lstat(lexer, i);
	}
	return (false);
}

bool	nothing_after_semi(t_list *lexer)
{
	while (lexer && ((t_token *)lexer->content)->token != SEMI)
	{
		if (is_strenum(((t_token *)lexer->content)->token))
			return (false);
		lexer = lexer->next;
	}
	return (true);
}

bool	check_semi(t_list *lexer)
{
	t_token	*token;
	bool	no_str;

	no_str = true;
	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (is_strenum(token->token))
			no_str = false;
		else if (token->token == SEMI)
		{
			if (no_str)
				return (false);
			else if (nothing_after_semi(lexer->next))
				token->rm = true;
			no_str = true;
		}
		lexer = lexer->next;
	}
	ft_lstremove_if(&lexer, lexer, is_removable, free_token);
	return (true);
}

bool	check_parsing(t_list *lexer)
{
	t_token	*token;
	t_list	*elem;
	size_t	i;

	i = 0;
	elem = lexer;
	while (elem)
	{
		token = (t_token *)elem->content;
		if ((token->token == CHEV_R || token->token == CHEV_L
			|| token->token == D_CHEV_R) && !check_chev(elem))
			return (false);
		else if (token->token == PIPE && !check_pipe(lexer, i))
			return (false);
		else if (token->token == SEMI && !check_semi(lexer))
			return (false);
		else if (elem->next && token->token == BASE
			&& is_redir(((t_token *)elem->next->content)->token)
			&& ((t_token *)elem->next->content)->token != PIPE)
			return (false);
		i++;
		elem = elem->next;
	}
	return (true);
}
