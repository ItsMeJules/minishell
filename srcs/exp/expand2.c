/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:58:17 by tvachera          #+#    #+#             */
/*   Updated: 2021/04/15 18:22:04 by tvachera         ###   ########.fr       */
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

int		is_removable(void *data1, void *data2)
{
	t_token	*token;

	(void)data2;
	token = (t_token *)data1;
	if (token->rm == true)
		return (0);
	return (1);
}

void	split_for_expand(t_token *token, t_list **lst)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (token->str[i])
	{
		j = i;
		while (token->str[i] && token->str[i] != 92 && token->str[i] != '$')
			i++;
		if (token->str[i] == '$' && i == j)
		{
			i++;
			while (token->str[i] && (!ft_strchr("\\$= ", token->str[i])
				|| (token->str[i] == '=' && i - j < 2)))
				i++;
		}
		else if (i == j)
		{
			i++;
			if (token->str[i] && ft_strchr("\\$", token->str[i]))
				i++;
		}
		ft_lstadd_back(lst, ft_lstnew(get_wbetw(j, i, token->str)));
	}
}

void	expand_split(t_list *split, t_list *env, t_list *vars, t_etype type)
{
	char	*str;

	while (split)
	{
		str = (char *)split->content;
		if (str[0] == '$')
			str = expand_dsign(str, env, vars);
		else if (str[0] == 92)
			str = expand_bslash(str, type);
		split->content = str;
		split = split->next;
	}
}

void	expand_field(t_list *lexer, t_list *env, t_list *vars)
{
	t_token	*token;
	t_list	*split;

	while (lexer && ((t_token *)lexer->content)->token != SEMI)
	{
		token = (t_token *)lexer->content;
		if (token->token == BASE || token->token == D_QUOTE)
		{
			split = 0;
			split_for_expand(token, &split);
			free(token->str);
			expand_split(split, env, vars, token->token);
			token->str = join_split(split);
			ft_lstclear(&split, free);
		}
		lexer = lexer->next;
	}
}
