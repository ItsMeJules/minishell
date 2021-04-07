/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:48:37 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/07 14:35:41 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_quote(t_iter *iter)
{
	size_t	i;
	t_token	*token;

	i = iter->i + 1;
	while (iter->line[i] && iter->line[i] != ''' && iter->line[i - 1] != '\\')
		i++;
	if (!iter->line[i])
	{
		iter->err = 10;
		return (0);
	}
	token = create_token(get_wbetw(iter->i + 1, i, iter->line), QUOTE);
	if (!token)
	{
		iter->err == 1;
		return 0;
	}
	iter->i = i + 1;
	return (ft_lstnew(token));
}

t_list	*get_dquote(t_iter *iter)
{
	size_t	i;
	t_token	*token;

	i = iter->i + 1;
	while (iter->line[i] && iter->line[i] != '"' && iter->line[i - 1] != '\\')
		i++;
	if (!iter->line[i])
	{
		iter->err = 11;
		return (0);
	}
	token = create_token(get_wbetw(iter->i + 1, i, iter->line), D_QUOTE);
	if (!token)
	{
		iter->err == 1;
		return (0);
	}
	iter->i = i + 1;
	return (ft_lstnew(token));
}
