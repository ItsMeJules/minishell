/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:37:38 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/21 15:13:15 by tvachera         ###   ########.fr       */
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
	i--;
	elem = ft_lstat(lexer, i);
	while (i >= 0 && ((t_token *)elem->content)->token != SEMI)
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
		i++;
		elem = elem->next;
	}
	return (true);
}
