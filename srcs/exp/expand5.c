/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:37:21 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/20 11:11:26 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	only_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (false);
		i++;
	}
	return (true);
}

void	link_chains(t_list *ch1, t_list *ch2)
{
	while (ch1 && ch1->next)
		ch1 = ch1->next;
	ch1->next = ch2;
}

void	split_word(t_list *lexer)
{
	t_list	*next;
	t_token	*new;
	char	**words;
	size_t	i;

	next = lexer->next;
	lexer->next = NULL;
	words = ft_split(((t_token *)lexer->content)->str, " ");
	free(((t_token *)lexer->content)->str);
	i = 0;
	while (words[i])
	{
		if (!i)
			((t_token *)lexer->content)->str = ft_strdup(words[i]);
		else
		{
			new = create_token(ft_strdup(words[i]), BASE);
			ft_lstadd_back(&lexer, ft_lstnew(new));
		}
		if (words[i + 1])
			ft_lstadd_back(&lexer, ft_lstnew(create_token(" ", SPACE)));
		i++;
	}
	link_chains(lexer, next);
	ft_free_split(words);
}

void	create_new_words(t_list *lexer)
{
	t_token	*token;

	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (token->token == BASE && ft_strchr(token->str, ' '))
			split_word(lexer);
		lexer = lexer->next;
	}
}
