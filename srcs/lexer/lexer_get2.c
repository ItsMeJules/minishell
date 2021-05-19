/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:34:59 by jules             #+#    #+#             */
/*   Updated: 2021/05/19 15:02:37 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_semic(t_iter *iter)
{
	t_token	*token;

	token = create_token(";", SEMI);
	iter->i++;
	if (!token)
	{
		iter->err = ERR_MALLOC;
		return (NULL);
	}
	return (ft_lstnew(token));
}

char	*get_wbetw_wd(size_t start, size_t end, size_t nb_esc, char *line)
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
			if (ft_strchr(SPECIAL_CHARS, line[start]) && start < end)
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

size_t	get_word_bis(t_iter *iter, size_t *nb_esc)
{
	size_t	i;
	int		bslash;

	i = iter->i;
	while (iter->line[i] && iter->line[i] != ' '
		&& !ft_strchr(SPECIAL_CHARS, iter->line[i]))
	{
		if (iter->line[i] == 92)
		{
			bslash = count_backslash(&iter->line[i]);
			while (iter->line[i] == 92)
				i++;
			if (bslash % 2 != 0 && iter->line[i]
				&& ft_strchr(SPECIAL_CHARS, iter->line[i]))
			{
				i++;
				(*nb_esc)++;
			}
		}
		else
			i++;
	}
	return (i);
}

t_list	*get_word(t_iter *iter)
{
	size_t	i;
	t_token	*token;
	size_t	nb_esc;

	nb_esc = 0;
	i = get_word_bis(iter, &nb_esc);
	token = create_token(get_wbetw_wd(iter->i, i, nb_esc, iter->line), BASE);
	if (!token)
	{
		iter->err = ERR_MALLOC;
		return (NULL);
	}
	iter->i = i;
	return (ft_lstnew(token));
}
