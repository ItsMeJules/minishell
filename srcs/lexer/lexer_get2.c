/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:34:59 by jules             #+#    #+#             */
/*   Updated: 2021/04/07 13:37:16 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_semic(t_iter *iter)
{
	t_token	*token;
	
	token = create_token(ft_strdup(";"), CHEV_L);
	iter->i++;
	if (!token)
	{
		iter->err = 1; 
		return (NULL);
	}
	return (ft_lstnew(token));
}

t_list	*get_word(t_iter *iter)
{
	size_t	begin;
	t_token	*token;

	begin = iter->i;
	while (!iter->line[iter->i] && !iter->line[iter->i] == ' '
			&& !ft_strchr(SPECIAL_CHARS, iter->line[iter->i]))
		iter->i++;
	token = create_token(get_wbetw(begin, i, iter->line), BASE);
	if (!token)
	{
		inter->err = 1;
		return (NULL);
	}
	return (ft_lstnew(token));
}
