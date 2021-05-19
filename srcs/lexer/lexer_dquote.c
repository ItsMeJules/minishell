/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:44:42 by jules             #+#    #+#             */
/*   Updated: 2021/05/19 15:00:18 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_wbetw_dq(size_t start, size_t end, size_t nb_esc, char *line)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * (end - start - nb_esc + 1));
	if (!str)
		return (0);
	while (start < end)
	{
		if (line[start] == 92)
		{
			while (line[start] == 92)
				str[i++] = line[start++];
			if (line[start] == '"' && start < end)
			{
				str[--i] = line[start++];
				i++;
			}
		}
		else
			str[i++] = line[start++];
	}
	str[i] = 0;
	return (str);
}

size_t	get_quote_bis(t_iter *iter, size_t *nb_esc)
{
	size_t	i;
	int		bslash;

	i = iter->i + 1;
	while (iter->line[i] && iter->line[i] != '"')
	{
		if (iter->line[i] == 92)
		{
			bslash = count_backslash(&iter->line[i]);
			while (iter->line[i] == 92)
				i++;
			if (bslash % 2 != 0 && iter->line[i++] == '"')
				(*nb_esc)++;
		}
		else
			i++;
	}
	return (i);
}

t_list	*get_dquote(t_iter *iter)
{
	size_t	i;
	t_token	*token;
	size_t	nb_esc;

	nb_esc = 0;
	i = get_quote_bis(iter, &nb_esc);
	if (!iter->line[i])
	{
		iter->err = ERR_DQUOTE_NOT_CLOSED;
		return (0);
	}
	token = create_token(get_wbetw_dq(iter->i + 1, i, nb_esc, iter->line),
			D_QUOTE);
	if (!token)
	{
		iter->err = ERR_MALLOC;
		return (0);
	}
	iter->i = i + 1;
	return (ft_lstnew(token));
}
