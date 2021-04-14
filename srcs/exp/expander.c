/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:45:54 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/14 18:21:43 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_env(t_list *env, char *var)
{
	t_env	*elem;

	while (env)
	{
		elem = (t_env *)env->content;
		if (!ft_strcmp(var, elem->var))
			return (true);
		env = env->next;
	}
	return (false);
}

bool	is_declaration_field(t_list *lexer)
{
	t_token	*token;

	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (token->token == SEMI)
			return (true);
		else if ((token->token != BASE && token->token != SPACE)
			|| (token->token == BASE && !ft_strchr(token->str, '=')))
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
		if (token->token == SEMI)
			return ;
		else if (token->token == BASE)
		{
			var = get_var_from_str(token->str);
			val = get_val_from_str(token->str);
			if (is_env(*env, var))
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
			|| (token->token == BASE && !ft_strchr(token->str, '=')))
			return ;
		token->rm = true;
		lexer = lexer->next;
	}
}

int		is_removable(void *data1, void *data2)
{
	t_token	*token;

	(void)data2;
	token = (t_token *)data1;
	if (token->rm == true)
		return (0);
	return (1);
}

void	get_vars(t_list **lexer, t_list **env, t_list **vars)
{
	t_list	*temp;

	temp = *lexer;
	while (temp)
	{
		if (is_declaration_field(temp))
			add_vars(temp, env, vars);
		else
			mark_useless_declarations(temp);
		while (temp && ((t_token *)temp->content)->token != SEMI)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
	ft_lstremove_if(lexer, *env, is_removable, free_token);
}
