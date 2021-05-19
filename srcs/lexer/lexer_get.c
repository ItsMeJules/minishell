/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:48:37 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 15:01:19 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_quote(t_iter *iter)
{
	size_t	i;
	t_token	*token;

	i = iter->i + 1;
	while (iter->line[i] && iter->line[i] != 39)
		i++;
	if (!iter->line[i])
	{
		iter->err = ERR_QUOTE_NOT_CLOSED;
		return (0);
	}
	token = create_token(get_wbetw(iter->i + 1, i, iter->line), QUOTE);
	if (!token)
	{
		iter->err = ERR_MALLOC;
		return (0);
	}
	iter->i = i + 1;
	return (ft_lstnew(token));
}

t_list	*get_lchev(t_iter *iter)
{
	t_token	*token;

	token = create_token("<", CHEV_L);
	iter->i++;
	if (!token)
	{
		iter->err = ERR_MALLOC;
		return (NULL);
	}
	return (ft_lstnew(token));
}

t_list	*get_rchev(t_iter *iter)
{
	t_token	*token;

	if (iter->line[iter->i + 1] && iter->line[iter->i + 1] == '>')
	{
		token = create_token(">>", D_CHEV_R);
		iter->i += 2;
	}
	else
	{
		token = create_token(">", CHEV_R);
		iter->i++;
	}
	if (!token)
	{
		iter->err = ERR_MALLOC;
		return (NULL);
	}
	return (ft_lstnew(token));
}

t_list	*get_pipe(t_iter *iter)
{
	t_token	*token;

	token = create_token("|", PIPE);
	iter->i++;
	if (!token)
	{
		iter->err = ERR_MALLOC;
		return (NULL);
	}
	return (ft_lstnew(token));
}
