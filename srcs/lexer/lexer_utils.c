/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:24:06 by jules             #+#    #+#             */
/*   Updated: 2021/04/07 12:37:08 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	free(token->token);
	free(token);
}

void	tokenize_input(t_iter *iter, t_list *root)
{
	size_t			i;
	static t_spf	tab = {{''', get_quote}, {'"', get_dquote},
		{"<", get_lchev}, {">", get_rchev}, {';', get_semic}, {'|', get_pipe},
		{0, 0}};

	i = 0;
	while (iter->line[iter->i] && iter->err == 0)
	{
		if (!tab[i].spe)
		{
			ft_lstadd_back(&root, get_word(iter));
			i = 0;
			continue ;
		}
		else if (iter->line[iter->i] == tab[i].spe)
			ft_lstadd_back(&root, tab[i].f(iter));
		i++;
	}
	if (iter->err != 0)
		ft_lstclear(&root, free_token);
}
