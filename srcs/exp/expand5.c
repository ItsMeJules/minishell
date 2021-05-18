/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:37:21 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/18 12:52:54 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_chains(t_list *ch1, t_list *ch2)
{
	while (ch1 && ch1->next)
		ch1 = ch1->next;
	ch1->next = ch2;
}

t_list	*split_word(t_list *lexer)
{
	t_list	*split;
	t_token	*new;
	char	**words;
	size_t	i;

	split = NULL;
	words = ft_split(((t_token *)lexer->content)->str, " ");
	i = 0;
	while (words[i])
	{
		new = create_token(ft_strdup(words[i]), BASE);
		ft_lstadd_back(&split, ft_lstnew(new));
		if (words[i + 1])
			ft_lstadd_back(&split, ft_lstnew(create_token(" ", SPACE)));
		i++;
	}
	link_chains(split, lexer->next);
	ft_lstdelone(lexer, &free_token);
	ft_free_split(words);
	return (split);
}

void	create_new_words(t_list **lexer)
{
	t_list	*prev;
	t_token	*token;

	token = (t_token *)(*lexer)->content;
	if (token->token == BASE && ft_strchr(token->str, ' '))
		*lexer = split_word(*lexer);
	prev = *lexer;
	while (prev && prev->next)
	{
		token = (t_token *)prev->next->content;
		if (token->token == BASE && ft_strchr(token->str, ' '))
			prev->next = split_word(prev->next);
		prev = prev->next;
	}
}
