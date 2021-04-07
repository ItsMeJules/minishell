/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:24:06 by jules             #+#    #+#             */
/*   Updated: 2021/04/07 16:04:42 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *vtoken)
{
	free(((t_token *)vtoken)->str);
	free(vtoken);
}

t_list	*tokenize_input(t_iter *iter)
{
	size_t			i;
	t_list			*elem;
	t_list			*root;
	static t_spf	funcs[] = {{39, get_quote}, {34, get_dquote},
		{'<', get_lchev}, {'>', get_rchev}, {';', get_semic}, {'|', get_pipe},
		{0, get_word}};

	root = NULL;
	while (iter->line[iter->i])
	{
		i = 0;
		while (iter->line[iter->i] == ' ')
			iter->i++;
		while (funcs[i].spe && funcs[i].spe != iter->line[iter->i])
			i++;
		elem = funcs[i].f(iter);
		if (iter->err != 0)
		{
			// GESTION ERR
			ft_lstclear(&root, free_token);
			return (NULL);
		}
		ft_lstadd_back(&root, elem);
	}	
	return (root);
}
