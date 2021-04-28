/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:38:53 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/27 16:32:40 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(bool leaf, char **argv, t_list *redirs)
{
	t_node	*new;

	if (!(new = malloc(sizeof(t_node))))
		return (0);
	new->leaf = leaf;
	new->argv = argv;
	new->redirs = redirs;
	return (new);
}

size_t	nb_words(t_list *lexer)
{
	size_t	i;

	i = 0;
	while (lexer && ((t_token *)lexer->content)->token != PIPE
		&& ((t_token *)lexer->content)->token != SEMI)
	{
		if (is_chev(((t_token *)lexer->content)->token))
			lexer = lexer->next;
		else
			i++;
		lexer = lexer->next;
	}
	return (i);
}

char	**fill_argv(t_list *lexer, size_t size)
{
	char	**argv;
	int		i;

	if (!(argv = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (lexer && ((t_token *)lexer->content)->token != PIPE
		&& ((t_token *)lexer->content)->token != SEMI)
	{
		if (is_chev(((t_token *)lexer->content)->token))
			lexer = lexer->next;
		else
		{
			argv[i] = ft_strdup(((t_token *)lexer->content)->str);
			i++;
		}
		lexer = lexer->next;
	}
	argv[i] = NULL;
	return (argv);
}

bool	is_chev(t_etype type)
{
	return (type == CHEV_R || type == D_CHEV_R || type == CHEV_L);
}

bool	is_redir(t_etype type)
{
	return (is_chev(type) || type == PIPE);
}
