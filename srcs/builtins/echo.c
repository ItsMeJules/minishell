/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:20:02 by jules             #+#    #+#             */
/*   Updated: 2021/04/26 14:26:15 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	skip_options(t_list **lexer, bool *nl)
{
	if (*nl)
		return (false);
	while (*lexer && ft_strcmp(((t_token *)(*lexer)->content)->str, "-n") == 0)
	{
		*nl = true;
		*lexer = (*lexer)->next;
	}
	return (!(*lexer));
}

void	print_params(t_list *lexer, bool *printed)
{
	t_token	*token;

	*printed = true;
	token = (t_token *)lexer->content;
	ft_putstr_fd(token->str, 1);
	if (lexer->next && is_strenum(token->token))
		ft_putchar_fd(' ', 1);
}

int		ft_echo(t_list *lexer)
{
	t_token	*token;
	bool	nl;
	bool	printed;

	nl = false;
	printed = false;
	lexer = lexer->next; //skips the arg echo
	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (is_strenum(token->token))
		{
			if (!printed)
			{
				if (skip_options(&lexer, &nl))
					return (1);
			}
			print_params(lexer, &printed);
		}
		lexer = lexer->next;
	}
	if (!nl)
		ft_putchar_fd('\n', 1);
	return (1);
}
