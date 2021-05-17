/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:19:51 by tvachera          #+#    #+#             */
/*   Updated: 2021/05/11 15:52:03 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disp_lexer(t_list *root)
{
	t_token	*data;

	while (root)
	{
		data = (t_token *)root->content;
		if (data->token == QUOTE)
			printf("TYPE : QUOTE --- ");
		else if (data->token == D_QUOTE)
			printf("TYPE : D_QUOTE --- ");
		else if (data->token == PIPE)
			printf("TYPE : PIPE --- ");
		else if (data->token == CHEV_R)
			printf("TYPE : CHEV_R --- ");
		else if (data->token == CHEV_L)
			printf("TYPE : CHEV_L --- ");
		else if (data->token == D_CHEV_R)
			printf("TYPE : D_CHEV_R --- ");
		else if (data->token == SEMI)
			printf("TYPE : SEMI --- ");
		else if (data->token == SPACE)
			printf("TYPE : SPACE --- ");
		else
			printf("TYPE : BASE --- ");
		printf("STR : %s\n", data->str);
		root = root->next;
	}
}

void	disp_vars(t_list *vars)
{
	char	**envp;
	size_t	i;

	envp = get_envp(vars);
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		free(envp[i]);
		i++;
	}
	free(envp);
}
