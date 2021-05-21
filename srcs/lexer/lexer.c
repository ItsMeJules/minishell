/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:24:06 by jules             #+#    #+#             */
/*   Updated: 2021/05/21 13:47:10 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *vtoken)
{
	t_token	*token;

	token = (t_token *)vtoken;
	if ((token->token == QUOTE || token->token == D_QUOTE
			|| token->token == BASE) && token->str)
		free(((t_token *)vtoken)->str);
	free(vtoken);
}

t_list	*get_spaces(t_iter *iter)
{
	t_token	*token;

	while (iter->line[iter->i] && iter->line[iter->i] == 32)
		iter->i++;
	token = create_token(" ", SPACE);
	if (!token)
	{
		iter->err = ERR_MALLOC;
		return (NULL);
	}
	return (ft_lstnew(token));
}

t_list	*tokenize_input(t_iter *iter)
{
	size_t			i;
	t_list			*elem;
	t_list			*root;
	static t_spf	funcs[] = {{39, get_quote}, {34, get_dquote},
		{'<', get_lchev}, {'>', get_rchev}, {';', get_semic}, {'|', get_pipe},
		{' ', get_spaces}, {0, get_word}};

	root = NULL;
	while (iter->line && iter->line[iter->i])
	{
		i = 0;
		while (funcs[i].spe && funcs[i].spe != iter->line[iter->i])
			i++;
		elem = funcs[i].f(iter);
		ft_lstadd_back(&root, elem);
		if (iter->err)
			return (root);
	}	
	return (root);
}
