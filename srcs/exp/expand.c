/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:45:54 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/19 14:34:12 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_declaration_field(t_list *lexer)
{
	t_token	*token;

	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (token->token != BASE && token->token != SPACE)
		{
			if (token->token == PIPE || token->token == QUOTE
				|| token->token == D_QUOTE)
				return (false);
			return (true);
		}
		else if (token->token == BASE && !is_declaration(token->str))
			return (false);
		while (lexer && (((t_token *)lexer->content)->token == BASE
				|| ((t_token *)lexer->content)->token == D_QUOTE
				|| ((t_token *)lexer->content)->token == QUOTE))
			lexer = lexer->next;
		if (lexer && ((t_token *)lexer->content)->token == SPACE)
			lexer = lexer->next;
	}
	return (true);
}

void	set_var(char *str, t_list **env, t_list **vars)
{
	char	*var;
	char	*val;

	if (!str)
		return ;
	var = get_var_from_str(str);
	val = get_val_from_str(str);
	if (is_var(*env, var) && is_joinable(str))
		concat_var(env, var, val);
	else if (is_var(*vars, var) && is_joinable(str))
		concat_var(vars, var, val);
	else if (is_var(*env, var))
		mod_env2(env, var, val);
	else
		mod_env2(vars, var, val);
	free(str);
}

void	add_and_expand(t_list *lexer, t_list **env, t_list **vars)
{
	char	*str;

	while (lexer)
	{
		str = 0;
		if (((t_token *)lexer->content)->token != SPACE
			&& ((t_token *)lexer->content)->token != BASE)
			return ;
		while (lexer && is_strenum(((t_token *)lexer->content)->token))
		{
			expand_elem(lexer, *env, *vars);
			str = join_declaration(str, lexer->content);
			((t_token *)lexer->content)->rm = true;
			lexer = lexer->next;
		}
		set_var(str, env, vars);
		if (lexer && ((t_token *)lexer->content)->token == SPACE)
		{
			((t_token *)lexer->content)->rm = true;
			lexer = lexer->next;
		}
	}
}

void	mark_useless_declarations(t_list *lexer)
{
	t_token	*token;

	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (token->token == SEMI
			|| (token->token != BASE && token->token != SPACE)
			|| (token->token == BASE && !is_declaration(token->str)))
			return ;
		token->rm = true;
		lexer = lexer->next;
	}
}

void	expand(t_list **lexer, t_list **env, t_list **vars, t_etype type)
{
	if (type == CMD && is_declaration_field(*lexer))
		add_and_expand(*lexer, env, vars);
	else if (type == CMD)
	{
		mark_useless_declarations(*lexer);
		expand_field(*lexer, *env, *vars);
	}
	else if (type == FL)
		expand_field(*lexer, *env, *vars);
	concat_chains(*lexer);
	ft_lstremove_if(lexer, *lexer, is_removable, free_token);
	lst_rmdspace(lexer);
	lst_rmempty(lexer);
	lst_rmdsemi(lexer);
}
