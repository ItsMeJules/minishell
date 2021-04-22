/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_elems.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:48:59 by jpeyron           #+#    #+#             */
/*   Updated: 2021/04/22 16:54:35 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*next_sep(t_list *lexer)
{
	static t_list	*elem = NULL;
	static bool		end = false;
	t_token			*token;

	if (end)
		return (NULL);
	if (!elem)
		elem = lexer;
	else
		elem = elem->next;
	while (elem)
	{
		token = (t_token *)elem->content;
		if (token->token == SEMI)
			return (new_node(SEMI, NULL));
		elem = elem->next;
	}
	end = true;
	return (NULL);
}

t_node	*next_redir(t_list *lexer)
{
	static t_list	*elem = NULL;
	static bool		end = false;
	t_token			*token;

	if (end)
		return (NULL);
	if (!elem)
		elem = lexer;
	else
		elem = elem->next;
	while (elem && ((t_token *)elem->content)->token != SEMI)
	{
		token = (t_token *)elem->content;
		if (!is_strenum(token->token))
			return (new_node(token->token, NULL));
		elem = elem->next;
	}
	if (!elem)
		end = true;
	return (NULL);
}

t_node	*cmd_pipe(t_list *lexer)
{
	static t_list	*elem = NULL;

	if (!elem)
		elem = lexer;
	while (elem && ((t_token *)elem->content)->token != PIPE)
		elem = elem->next;
	elem = elem->next;
	return (new_node(COMMAND, fill_argv(elem, nb_words(elem))));
}

t_node	*get_file(t_list *lexer)
{
	static t_list	*elem = NULL;

	if (!elem)
		elem = lexer;
	while (elem && !is_chev(((t_token *)elem->content)->token))
		elem = elem->next;
	elem = elem->next;
	return (new_node(FILE_, ft_strdup(((t_token *)elem->content)->str)));
}

t_node	*get_cmd(t_list *lexer)
{
	static t_list	*elem = NULL;
	static bool		end = false;
	t_token			*token;
	char			**argv;

	if (end)
		return (NULL);
	if (!elem)
		elem = lexer;
	else
		elem = elem->next;
	argv = fill_argv(elem, nb_words(elem));
	while (elem && ((t_token *)elem->content)->token != SEMI)
		elem = elem->next;
	if (!elem)
		end = true;
	return (new_node(COMMAND, argv));
}
