/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:45:54 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/20 11:41:08 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_declaration(char *str)
{
	size_t	i;

	i = 0;
	if (!ft_strchr(str, '='))
		return (false);
	while (str[i] != '=')
		i++;
	if (!i)
		return (false);
	if (str[i - 1] == 92)
		return (false);
	return (true);
}

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
		lexer = lexer->next;
	}
	return (true);
}

void	add_vars(t_list *lexer, t_list **env, t_list **vars)
{
	t_token	*token;
	char	*var;
	char	*val;

	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (token->token != BASE && token->token != SPACE)
			return ;
		else if (token->token == BASE)
		{
			var = get_var_from_str(token->str);
			val = get_val_from_str(token->str);
			if (is_var(*env, var))
				mod_env(env, var, val);
			else
				mod_env(vars, var, val);
			free(var);
			free(val);
		}
		token->rm = true;
		lexer = lexer->next;
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

void	expand(t_list **lexer, t_list **env, t_list **vars)
{
	t_list	*temp;

	temp = *lexer;
	while (temp)
	{
		if (is_declaration_field(temp))
			add_vars(temp, env, vars);
		else
			mark_useless_declarations(temp);
		expand_field(temp, *env, *vars);
		while (temp && ((t_token *)temp->content)->token != SEMI)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
	ft_lstremove_if(lexer, *lexer, is_removable, free_token);
	lst_rmdspace(lexer);
	lst_rmdsemi(lexer);
}
