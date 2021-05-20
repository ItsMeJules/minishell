/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:50:57 by jpeyron           #+#    #+#             */
/*   Updated: 2021/05/20 17:44:09 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_after_pipe(t_list *lexer)
{
	if (!lexer || !lexer->next)
		return (false);
	while (lexer && ((t_token *)lexer->content)->token != SEMI)
	{
		if (is_strenum(((t_token *)lexer->content)->token)
			|| is_chev(((t_token *)lexer->content)->token))
			return (true);
		else if (((t_token *)lexer->content)->token != SPACE)
			return (false);
		lexer = lexer->next;
	}
	return (false);
}

bool	check_before_pipe(t_list *lexer, int i)
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
