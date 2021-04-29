/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:26:43 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/29 16:07:35 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_rmempty(t_list **alst)
{
	t_token	*elem;
	t_list	*lst;

	lst = *alst;
	while (lst)
	{
		elem = (t_token *)lst->content;
		if (elem->token == BASE && !ft_strlen(elem->str))
			elem->rm = true;
		lst = lst->next;
	}
	ft_lstremove_if(alst, *alst, is_removable, free_token);
}

char	*join_declaration(char *str, t_token *token)
{
	char	*tmp;

	if (!str)
		str = ft_strdup(token->str);
	else
	{
		tmp = str;
		str = ft_strjoin(str, token->str);
		free(tmp);
	}
	return (str);
}

bool	is_strenum(t_etype type)
{
	if (type == BASE || type == D_QUOTE || type == QUOTE)
		return (true);
	return (false);
}

void	concat_chains(t_list *lexer)
{
	t_token	*token;
	
	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (is_strenum(token->token))
		{
			lexer = lexer->next;
			while (lexer && is_strenum(((t_token *)lexer->content)->token))
			{
				((t_token *)lexer->content)->rm = true;
				token->str = join_declaration(token->str, lexer->content);
				lexer = lexer->next;
			}
		}
		if (lexer)
			lexer = lexer->next;
	}
}
