/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:34:59 by jules             #+#    #+#             */
/*   Updated: 2021/04/08 15:15:58 by jules            ###   ########.fr       */
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
		iter->err = ERR_MALLOC; 
		return (NULL);
	}
	return (ft_lstnew(token));
}

t_list	*get_word(t_iter *iter)
{
	size_t	i;
	t_token	*token;

	i = iter->i;
	while (iter->line[i] && iter->line[i] != ' '
			&& !ft_strchr(SPECIAL_CHARS, iter->line[i]))
		i++;
	token = create_token(get_wbetw(iter->i, i, iter->line), BASE);
	if (!token)
	{
		iter->err = ERR_MALLOC;
		return (NULL);
	}
	iter->i = i;
	return (ft_lstnew(token));
}
